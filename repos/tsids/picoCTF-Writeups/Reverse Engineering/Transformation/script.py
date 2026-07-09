flag = open("enc").read()
print(''.join([chr(ord(flag[i]) >> 8) + chr(ord(flag[i]) -
      ((ord(flag[i]) >> 8) << 8)) for i in range(len(flag))]))
