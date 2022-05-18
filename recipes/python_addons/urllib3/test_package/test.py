import urllib3

http = urllib3.PoolManager()

# doesn't work if a proxy server must be used. urllib doesn't
# use/respect the corresponding environment variables (http_proxy ...)

#r = http.request('GET', 'http://example.com')
#print(r.status)
