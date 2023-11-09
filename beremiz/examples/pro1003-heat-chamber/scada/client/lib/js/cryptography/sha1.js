//JAVASCRIPT DOCUMENT


/*	SHA-1 CRYPTOGRAPHIC HASH ALGORITHM
*
*	A cryptographic hash (sometimes called ‘digest’) is a kind of ‘signature’
*	for a text or a data file. SHA1 generates an almost-unique 160-bit (20-byte)
*	signature for a text. See below for the source code.
*
*	A hash is not ‘encryption’ – it cannot be decrypted back to the original text
*	(it is a ‘one-way’ cryptographic function, and is a fixed size for any size of
*	source text). This makes it suitable when it is appropriate to compare ‘hashed’
*	versions of texts, as opposed to decrypting the text to obtain the original version.
*	Such applications include stored passwords, challenge handshake authentication, and
*	digital signatures.
*
*		- to validate a password, you can store a hash of the password,
*			then when when the password is to be authenticated, you hash
*			the password the user supplies, and if the hashed versions match,
*			the password is authenticated; but the original password cannot be
*			obtained from the stored hash;
*
*		- ‘challenge handshake authentication’ (or ‘challenge hash authentication’)
*			avoids transmissing passwords in ‘clear’ – a client can send the hash of
*			a password over the internet for validation by a server without risk of
*			the original password being intercepted;
*
*		- anti-tamper – link a hash of a message to the original, and the recipient
*			can re-hash the message and compare it to the supplied hash: if they match,
*			the message is unchanged; this can also be used to confirm no data-loss
*			in transmission;
*
*		 - digital signatures are rather more involved, but in essence, you can sign
*			the hash of a document by encrypting it with your private key, producing
*			a digital signature for the document. Anyone else can then check that you
*			authenticated the text by decrypting the signature with your public key to
*			obtain the original hash again, and comparing it with their hash of the text.
*
*	SHA-1 is one of the most secure hash algorithms. It is used in SSL (Secure Sockets Level),
*	PGP (Pretty Good Privacy), XML Signatures, and in Microsoft’s Xbox, among hundreds of
*	other applications (including from IBM, Cisco, Nokia, etc). It is defined in the NIST
*	(National Institute of Standards and Technology) standard ‘FIPS 180-2’. There is a
*	good description at Wikipedia.
*
*	Note on security: SHA-1 was subjected to cryptanalysis through 2005 which showed it to
*	be weaker than its theoretical strength. Cryptoanalysis is complex (and I’m no expert),
*	but Xiaoyun Wang effectively announced that given thousands of years of supercomputer
*	time, a ‘collision pair’ could be found. Even this, however, would be unlikely to be
*	exploited to compromise any real-life cryptographic hash (for which a ‘pre-image’
*	attack would be necessary). SHA1 is still extremely secure, for the moment. However,
*	NIST do recommend that federal agencies should migrate to SHA-2 algorithms for most
*	purposes by 2010.
*
*	In this JavaScript implementation, I have tried to make the script as clear and concise
*	as possible, and equally as close as possible to the NIST specification, to make the
*	operation of the script readily understandable.
*
*	This script is oriented toward hashing text messages rather than binary data. The standard
*	considers hashing byte-stream (or bit-stream) messages only. Text which contains (multi-byte)
*	characters outside ISO 8859-1 (i.e. accented characters outside Latin-1 or non-European
*	character sets – anything with Unicode code-point above U+FF), can’t be encoded 4-per-word,
*	so you will need to cater for those before passing the text to the hash algorithm, using
*	something such as UTF-8 encoding (see my AES page for an example).
*
*	Using IE on a 1GHz PIII machine, this script will process the message at a speed of around
*	20kb/sec.
*
*	If you need an encryption algorithm rather than a cryptographic hash algorithm, look at
*	my JavaScript implementation of TEA (Tiny Encryption Algorithm) or JavaScript implementation
*	of AES.
*
*	See below for the source code of the JavaScript implementation. You are welcome to re-use
*	these scripts [without any warranty express or implied] provided you retain my copyright
*	notice and when possible a link to my website (under a LGPL license). section numbers
*	relate the code back to sections in the standard. If you have any queries or find any
*	problems, please contact me.
*
*	(c)2002-2005 Chris Veness
*	scripts@movable-type.co.uk
*	http://www.movable-type.co.uk
*/

function sha1Hash(msg)
{
    // constants [§4.2.1]
    var K = [0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6];


    // PREPROCESSING 
 
    msg += String.fromCharCode(0x80); // add trailing '1' bit to string [§5.1.1]

    // convert string msg into 512-bit/16-integer blocks arrays of ints [§5.2.1]
    var l = Math.ceil(msg.length/4) + 2;  // long enough to contain msg plus 2-word length
    var N = Math.ceil(l/16);              // in N 16-int blocks
    var M = new Array(N);
    for (var i=0; i<N; i++) {
        M[i] = new Array(16);
        for (var j=0; j<16; j++) {  // encode 4 chars per integer, big-endian encoding
            M[i][j] = (msg.charCodeAt(i*64+j*4)<<24) | (msg.charCodeAt(i*64+j*4+1)<<16) | 
                      (msg.charCodeAt(i*64+j*4+2)<<8) | (msg.charCodeAt(i*64+j*4+3));
        }
    }
    // add length (in bits) into final pair of 32-bit integers (big-endian) [5.1.1]
    // note: most significant word would be ((len-1)*8 >>> 32, but since JS converts
    // bitwise-op args to 32 bits, we need to simulate this by arithmetic operators
    M[N-1][14] = ((msg.length-1)*8) / Math.pow(2, 32); M[N-1][14] = Math.floor(M[N-1][14])
    M[N-1][15] = ((msg.length-1)*8) & 0xffffffff;

    // set initial hash value [§5.3.1]
    var H0 = 0x67452301;
    var H1 = 0xefcdab89;
    var H2 = 0x98badcfe;
    var H3 = 0x10325476;
    var H4 = 0xc3d2e1f0;

    // HASH COMPUTATION [§6.1.2]

    var W = new Array(80); var a, b, c, d, e;
    for (var i=0; i<N; i++) {

        // 1 - prepare message schedule 'W'
        for (var t=0;  t<16; t++) W[t] = M[i][t];
        for (var t=16; t<80; t++) W[t] = ROTL(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);

        // 2 - initialise five working variables a, b, c, d, e with previous hash value
        a = H0; b = H1; c = H2; d = H3; e = H4;

        // 3 - main loop
        for (var t=0; t<80; t++) {
            var s = Math.floor(t/20); // seq for blocks of 'f' functions and 'K' constants
            var T = (ROTL(a,5) + f(s,b,c,d) + e + K[s] + W[t]) & 0xffffffff;
            e = d;
            d = c;
            c = ROTL(b, 30);
            b = a;
            a = T;
        }

        // 4 - compute the new intermediate hash value
        H0 = (H0+a) & 0xffffffff;  // note 'addition modulo 2^32'
        H1 = (H1+b) & 0xffffffff; 
        H2 = (H2+c) & 0xffffffff; 
        H3 = (H3+d) & 0xffffffff; 
        H4 = (H4+e) & 0xffffffff;
    }

    return H0.toHexStr() + H1.toHexStr() + H2.toHexStr() + H3.toHexStr() + H4.toHexStr();
}

//
// function 'f' [§4.1.1]
//
function f(s, x, y, z) 
{
    switch (s) {
    case 0: return (x & y) ^ (~x & z);           // Ch()
    case 1: return x ^ y ^ z;                    // Parity()
    case 2: return (x & y) ^ (x & z) ^ (y & z);  // Maj()
    case 3: return x ^ y ^ z;                    // Parity()
    }
}

//
// rotate left (circular left shift) value x by n positions [§3.2.5]
//
function ROTL(x, n)
{
    return (x<<n) | (x>>>(32-n));
}

//
// extend Number class with a tailored hex-string method 
//   (note toString(16) is implementation-dependant, and 
//   in IE returns signed numbers when used on full words)
//
Number.prototype.toHexStr = function()
{
    var s="", v;
    for (var i=7; i>=0; i--) { v = (this>>>(i*4)) & 0xf; s += v.toString(16); }
    return s;
}
