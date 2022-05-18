import snowballstemmer

stemmer = snowballstemmer.stemmer('english')
print(stemmer.stemWords("We are the world".split()))