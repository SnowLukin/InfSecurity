# Doesnt work with Pythong 3.9+
from Crypto.Hash import SHA256
from Crypto.PublicKey import ECC
from Crypto.Signature import DSS

# Generate a fresh ECC key pair
key = ECC.generate(curve='P-256')
print('Private key:', key.export_key(format='PEM'))
message = b'Hello, world!'
print('Message:', message)
h = SHA256.new(message)
signer = DSS.new(key, 'fips-186-3')
signature = signer.sign(h)
print('Signature:', signature.hex())

# Verify the signature
verifier = DSS.new(key, 'fips-186-3')
try:
    verifier.verify(h, signature)
    print("The signature is valid.")
except ValueError:
    print("The signature is not valid.")