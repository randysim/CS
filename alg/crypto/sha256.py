# sha-256 Implementation in Python
# Author: Randy Sim, Completion-Date: 05/22/2022
# referenced:
# https://www.researchgate.net/file.PostFileLoader.html?id=534b393ad3df3e04508b45ad&assetKey=AS%3A273514844622849%401442222429260
# https://csrc.nist.gov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf
# https://www.youtube.com/watch?v=f9EbD6iY9zI

# Struggles:
# the "+" in the guide is not the same thing as XOR
# the plus is addition mod 2^32

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
# initial hash values, fraction of the square root of the first 8 primes
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
    return A[l - rot_len:] + A[:l - rot_len]


def ShR(A, n):  # shift
    l = len(A)
    return "0" * min(n, l) + A[:l - n]


def Ch(X, Y, Z):  # choose (Determine output from Y and Z based on X)
    return '{0:b}'.format((int(X, 2) & int(Y, 2)) ^ ((~int(X, 2)) & int(Z, 2))).rjust(len(X), "0")


def Maj(X, Y, Z):  # chooses based on the majority of the bits X, Y, and Z
    return '{0:b}'.format((int(X, 2) & int(Y, 2)) ^ (int(X, 2) & int(Z, 2)) ^ (int(Y, 2) & int(Z, 2))).rjust(len(X), "0")


def o0(x):
    return '{0:b}'.format(int(RotR(x, 7), 2) ^ int(RotR(x, 18), 2) ^ int(ShR(x, 3), 2)).rjust(len(x), "0")


def o1(x):
    return '{0:b}'.format(int(RotR(x, 17), 2) ^ int(RotR(x, 19), 2) ^ int(ShR(x, 10), 2)).rjust(len(x), "0")


def e0(x):
    return '{0:b}'.format(int(RotR(x, 2), 2) ^ int(RotR(x, 13), 2) ^ int(RotR(x, 22), 2)).rjust(len(x), "0")


def e1(x):
    return '{0:b}'.format(int(RotR(x, 6), 2) ^ int(RotR(x, 11), 2) ^ int(RotR(x, 25), 2)).rjust(len(x), "0")


def preprocess(bstr):
    # accepts binary string input
    # returns list of 512 bit blocks

    blocks = []
    l = len(bstr)
    bstr += "1"  # separater

    n = int((l + 1) / 512)

    r = (l + 1) - (n * 512)  # remaining
    zeros = 0
    if r > 448:
        zeros = 960 - r
    else:
        zeros = 448 - r

    bstr += "0" * zeros

    # add 64 bit number rep
    bstr += '{0:064b}'.format(l)

    for i in range(n + 1):
        # 8 bits per char
        blocks.append(bstr[(i*512):(i + 1) * 512])

    return blocks


def mod32a(st):
    val = 0

    for x in st:
        val += int(x, 2)

    return val % (2 ** 32)


def g_next(schedule, t):
    return '{0:b}'.format(mod32a([o1(schedule[t - 2]), schedule[t - 7], o0(schedule[t-15]), schedule[t-16]])).rjust(len(schedule[0]), "0")

# create message schedule for a block


def c_sche(m_block):
    schedule = []
    for i in range(16):  # create the first 16 using existing block
        schedule.append(m_block[i * 32:(i + 1) * 32])
    # generate the rest of the schedule
    for k in range(48):
        schedule.append(g_next(schedule, k+16))

    return schedule


def compress(blocks):
    a = "{0:b}".format(I[0]).rjust(32, "0")
    b = "{0:b}".format(I[1]).rjust(32, "0")
    c = "{0:b}".format(I[2]).rjust(32, "0")
    d = "{0:b}".format(I[3]).rjust(32, "0")
    e = "{0:b}".format(I[4]).rjust(32, "0")
    f = "{0:b}".format(I[5]).rjust(32, "0")
    g = "{0:b}".format(I[6]).rjust(32, "0")
    h = "{0:b}".format(I[7]).rjust(32, "0")

    for block in blocks:
        schedule = c_sche(block)

        for i in range(len(schedule)):
            t1 = "{0:b}".format(mod32a([e1(e), Ch(e, f, g),
                                        h, "{0:b}".format(K[i]).rjust(32, "0"), schedule[i]])).rjust(32, "0")
            t2 = "{0:b}".format(mod32a([e0(a), Maj(a, b, c)])).rjust(32, "0")

            h = g
            g = f
            f = e
            e = "{0:b}".format(mod32a([d, t1])).rjust(32, "0")
            d = c
            c = b
            b = a
            a = "{0:b}".format(mod32a([t1, t2])).rjust(32, "0")
    a = "{0:b}".format(mod32a(["{0:b}".format(I[0]), a])).rjust(32, "0")
    b = "{0:b}".format(mod32a(["{0:b}".format(I[1]), b])).rjust(32, "0")
    c = "{0:b}".format(mod32a(["{0:b}".format(I[2]), c])).rjust(32, "0")
    d = "{0:b}".format(mod32a(["{0:b}".format(I[3]), d])).rjust(32, "0")
    e = "{0:b}".format(mod32a(["{0:b}".format(I[4]), e])).rjust(32, "0")
    f = "{0:b}".format(mod32a(["{0:b}".format(I[5]), f])).rjust(32, "0")
    g = "{0:b}".format(mod32a(["{0:b}".format(I[6]), g])).rjust(32, "0")
    h = "{0:b}".format(mod32a(["{0:b}".format(I[7]), h])).rjust(32, "0")

    return '{0:06x}'.format(int(a, 2)) + '{0:06x}'.format(int(b, 2)) + '{0:06x}'.format(int(c, 2)) + '{0:06x}'.format(int(d, 2)) + '{0:06x}'.format(int(e, 2)) + '{0:06x}'.format(int(f, 2)) + '{0:06x}'.format(int(g, 2)) + '{0:06x}'.format(int(h, 2))


def sha256(str):
    str_bin = to_bin(str)
    prep = preprocess(str_bin)
    return compress(prep)


val = input("Enter string to be hashed:")
ans = sha256(val)
print(ans)
