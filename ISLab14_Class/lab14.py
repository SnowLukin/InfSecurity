from pygost.gost3410 import CURVES
# curve it is a dictionary with the following keys to access the values:

curve = CURVES["id-tc26-gost-3410-12-512-paramSetA"]
from os import urandom

# prw_raw is a random number of 64 bytes
prv_raw = urandom(64)
from pygost.gost3410 import prv_unmarshal
from pygost.gost3410 import prv_marshal

# prv is a private key object, which is a tuple of two elements
prv = prv_unmarshal(prv_raw)

# print the private key
print("Private key: ", prv)

# prv_raw2 is a raw private key
prv_raw = prv_marshal(curve, prv)
from pygost.gost3410 import public_key
# pub is a public key object, which is a tuple of two elements
pub = public_key(curve, prv)
from pygost.gost3410 import pub_marshal
from pygost.utils import hexenc
print("Public key is:", hexenc(pub_marshal(pub)))

# data for signing it is the message to be signed
data_for_signing = b"some data"

# dgst is a hash of the message
from pygost import gost34112012512
dgst = gost34112012512.new(data_for_signing).digest()

# signature
from pygost.gost3410 import sign
signature = sign(curve, prv, dgst)

# verification
from pygost.gost3410 import verify
verify(curve, pub, dgst, signature)
print("Signature is:", hexenc(signature))
print("Signature result is:", verify(curve, pub, dgst, signature))