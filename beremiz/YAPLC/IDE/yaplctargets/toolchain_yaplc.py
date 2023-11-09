import os, sys
from util.ProcessLogger import ProcessLogger
from targets.toolchain_gcc import toolchain_gcc

toolchain_dir  = os.path.dirname(os.path.realpath(__file__))
base_dir       = os.path.join(os.path.join(toolchain_dir, ".."), "..")
plc_rt_dir     = os.path.join(os.path.join(base_dir, "RTE"), "src")
if (os.name == 'posix' and not os.path.isfile(plc_rt_dir)):
    plc_rt_dir = os.environ["HOME"]+"/YAPLC/RTE/src"
    base_dir   = os.environ["HOME"]+"/YAPLC"

class toolchain_yaplc(toolchain_gcc):
    def __init__(self, CTRInstance):
        self.dev_family       = "NO_DEVICE"
        self.load_addr        = "0"
        self.runtime_addr     = "0"
        self.base_flags       = ["-mthumb", "-mcpu=cortex-m4", "-g3", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16"]
        
        if os.name in ("nt", "ce"):
	    prefix_dir    = os.path.join(os.path.join(base_dir, "gnu-arm-embedded"), "bin")
            self.toolchain_prefix = prefix_dir + "\\arm-none-eabi-"
        else:
            self.toolchain_prefix = "arm-none-eabi-"
            
        self.linker_script    = ""
        self.extension        = ".elf"
        toolchain_gcc.__init__(self, CTRInstance)

    def getBuilderCFLAGS(self):
        """
        Returns list of builder specific CFLAGS
        """
        flags = self.base_flags 
        flags += ["-std=gnu11", "-Wall", "-fdata-sections", "-ffunction-sections", "-fno-strict-aliasing", "-Wno-unused-variable", "-Wno-unused-but-set-variable"]
        flags += ["-D"+ self.dev_family] 
        flags += ["-I\"" + plc_rt_dir + "\""]
        if hasattr(self, 'find_dirs'):
	    flags += self.find_dirs
        flags += ["-DPLC_RTE_ADDR=" + self.runtime_addr]
        flags += self.cflags
        return flags + [self.CTRInstance.GetTarget().getcontent().getCFLAGS()]

    def getBuilderLDFLAGS(self):
        """
        Returns list of builder specific LDFLAGS
        """
        flags = self.base_flags
        flags += ["-Xlinker", "-T \"" + self.linker_script + "\""]
        flags += ["-Wl,--gc-sections", "-nostartfiles"]
        #flags += ["-Wl,-Map=\"" + self.exe_path + ".map\""]
        return flags + [self.CTRInstance.GetTarget().getcontent().getLDFLAGS()]

    def getCompiler(self):
        """
        Returns compiler
        """
        return self.toolchain_prefix + "gcc"
      
    def getLinker(self):
        """
        Returns linker
        """
        return self.toolchain_prefix + "g++"
        
    def calc_md5(self):
        return toolchain_gcc.calc_source_md5(self)

    def build(self):
      
        #Build project
        self.cflags = ["-DPLC_MD5=" + self.calc_md5()]
        
        if toolchain_gcc.build(self):
	    #Run objcopy on success
	    self.CTRInstance.logger.write("   [OBJCOPY]  " + self.exe +" -> " + self.exe + ".hex\n")
	    
	    objcpy = [self.toolchain_prefix + "objcopy", "--change-address", self.load_addr,  "-O", "ihex", self.exe_path, self.exe_path + ".hex"]
	    ProcessLogger( self.CTRInstance.logger, objcpy).spin()

            objcpy = [self.toolchain_prefix + "objcopy", "--change-address", self.load_addr,  "-O", "binary", self.exe_path, self.exe_path + ".bin"]
	    ProcessLogger( self.CTRInstance.logger, objcpy).spin()
	    
	    self.CTRInstance.logger.write("Output size:\n")
	    
	    size = [self.toolchain_prefix + "size", self.exe_path]
	    ProcessLogger( self.CTRInstance.logger, size).spin()

            self.CTRInstance.logger.write("md5:\n   " + self.calc_md5() + "\n")
            
            return True
        
        return False
