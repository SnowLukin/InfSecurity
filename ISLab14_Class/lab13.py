from gost34112012 import GOST34112012


# make hash object with default parameters
hashObject = GOST34112012()
# Update the hash value with data
message = b'Something Something'
hashObject.update(message)
print(message)
# get the digest
print(hashObject.hexdigest())
