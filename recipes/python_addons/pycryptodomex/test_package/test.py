from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes

data = b'secret data'

key = get_random_bytes(16)
cipher = AES.new(key, AES.MODE_EAX)
ciphertext, tag = cipher.encrypt_and_digest(data)

[ print(x) for x in (cipher.nonce, tag, ciphertext) ]
