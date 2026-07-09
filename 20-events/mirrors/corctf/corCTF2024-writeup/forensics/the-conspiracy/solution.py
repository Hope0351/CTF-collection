# Reverse the encrypt() function
def decrypt(final_message, keys):
  message_nums = []
  for i in range(len(final_message)):
    message_nums.append(final_message[i] / keys[i])

  message = ""
  for num in message_nums:
    message += chr(int(num))

  return message

# Build the orignal message by decrypting every final_message and key pair
decrypted_message = ""
with open("packet_data.txt", "r") as f:
  for i in range(26):
    final_message = f.readline().split(", ")
    final_message = [int(num) for num in final_message]
    
    keys = f.readline().split(", ")
    keys = [int(num) for num in keys]

    decrypted_message += decrypt(final_message, keys) + " "

print(decrypted_message)
