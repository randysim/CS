# sha-256 Implementation in Python
# Author: Randy Sim, Completion-Date:
# referenced:
# https://www.researchgate.net/file.PostFileLoader.html?id=534b393ad3df3e04508b45ad&assetKey=AS%3A273514844622849%401442222429260
# https://csrc.nist.gov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf
# https://www.youtube.com/watch?v=f9EbD6iY9zI

"""
steps:
preprocess - mod 448 512, last 64 bits represents length of bits
split into blocks of 512
create a message schedule using each block
compress constant values using message schedule
concatenate hex of each constant value together to get hash :D
"""

# generate constats, cube roots of the first 64 prime numbers
K = [0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
     0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
     0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
     0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
     0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
     0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
     0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
     0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
     0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
     0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
     0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
     0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
     0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
     0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
     0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
     0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2]
# initial hash values, square root of the first 8 primes
I = [0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19]


def to_bin(string):
    res = ""
    for x in string:
        res += format(ord(x), '08b')
    return res
    # return "".join(format(ord(x), 'b') for x in string)


def RotR(A, n):  # rotate
    # input: binary string of word, output: rotate it to the right n times
    l = len(A)
    rot_len = n % l
    return A[l - rot_len:] + A[rot_len-1:l - rot_len]


def ShR(A, n):  # shift
    l = len(A)
    return "0" * n + A[:l - n]


def Ch(X, Y, Z):  # choose (Determine output from Y and Z based on X)
    return (X & Y) ^ ((~X) & Z)


def Maj(X, Y, Z):  # chooses based on the majority of the bits X, Y, and Z
    return (X & Y) ^ (X & Z) ^ (Y & Z)


def preprocess(bstr):
    # accepts binary string input
    # returns list of 512 bit blocks

    bstr += "1"  # separater

    blocks = []
    n = int(len(bstr) / 512)

    for i in range(n):
        # 8 bits per char
        blocks.append(bstr[i*64:(i + 1) * 64])

    return blocks

# generate hash values, fractional values of square roots of the first 8 prime numbers


val = input("enter string to be encrypted: ")
bin = to_bin(val)
