# from pygost.gost34112012 import GOST34112012
from gost34112012 import GOST34112012
# make hash object with default parameters
hashObject = GOST34112012()
# Update the hash value with data
hashObject.update(b'Something Something')
# get the digest
print(hashObject.hexdigest())
