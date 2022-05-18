import chardet

print(chardet.detect("Hello World!".encode()))
print(chardet.detect("äüö".encode()))
print(chardet.detect("é".encode()))
