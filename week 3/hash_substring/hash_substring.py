import random

def read_input():
    return (raw_input().rstrip(), raw_input().rstrip())

def print_occurrences(output):
    print(' '.join(map(str, output)))

def get_occurrences_naive(pattern, text):
    return [
        i 
        for i in range(len(text) - len(pattern) + 1) 
        if text[i:i + len(pattern)] == pattern
    ]

def poly_hash(s, prime, x):
    ans = 0
    for c in reversed(s):
    	ans = (ans * x + ord(c)) % prime
    return ans

def precompute_hashes(text, plength, p, x):
    H = [0] * (len(text) - plength + 1)
    s = text[-plength:]
    H[len(text)-plength] = poly_hash(s, p, x)
    y = 1
    for i in range(1, plength+1):
        y = (y * x) % p
    for i in reversed(range(len(text) - plength)):
    	prehash = x * H[i + 1] + ord(text[i]) - y * ord(text[i + plength])
    	while(prehash < 0):
    		prehash += p
        H[i] = prehash % p
    return H

def get_occurrences(pattern, text):
    p = 1000000007
    x = random.randint(1, p)
    tlength = len(text)
    plength = len(pattern)
    phash = poly_hash(pattern, p, x)
    H = precompute_hashes(text, plength, p, x)
    return [
        i 
        for i in range(len(text) - len(pattern) + 1) 
        if phash == H[i] and text[i:i + len(pattern)] == pattern
    ]

if __name__ == '__main__':
    print_occurrences(get_occurrences(*read_input()))