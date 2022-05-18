import idna

a = 'ドメイン.テスト'
b = 'xn--eckwd4c7c.xn--zckzah'

assert idna.encode(a) == b.encode()
assert idna.decode(b) == a

print(idna.decode(b))
print(idna.encode(a))
