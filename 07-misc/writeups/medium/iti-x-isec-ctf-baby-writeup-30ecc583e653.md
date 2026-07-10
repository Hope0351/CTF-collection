# :game_die: ITI x iSEC CTF Baby Writeup. Hey there, been a while. Today, I’m…

---

After a few trials and errors, getting the image concatenated completely horizontally which was basically a very long horizontal line, I tried to fix it which led to an equally long but vertical line that was not intelligible.

Finally, I fixed my prompt and asked GPT to write a script that would concatenate the image parts in equal distribution over length and width, basically meaning it would divide the number of pixels to get the correct dimensions for the original image.

Here’s the script:

```
from PIL import Image
import os
import math

# Specify the source directory where your ordered images are located
source_directory = '/path/to/source_directory'

# List and sort the image files based on the numeric value after 'part_'
files = os.listdir(source_directory)
sorted_files = sorted(files, key=lambda x: int(x.split('_')[1].split('.')[0]))

# Load images
images = [Image.open(os.path.join(source_directory, file)) for file in sorted_files]

# Determine grid size
n = len(images)
grid_size = math.ceil(math.sqrt(n))

# Determine the mode for the final image (RGB or RGBA)
final_mode = 'RGBA' if any(img.mode == 'RGBA' for img in images) else 'RGB'

# Determine max width and height of the images
max_width = max(img.width for img in images)
max_height = max(img.height for img in images)

# Size of the grid
grid_width = grid_size * max_width
grid_height = grid_size * max_height

# Create a new image with the appropriate size and mode
concatenated_image = Image.new(final_mode, (grid_width, grid_height))

# Paste images into the grid
for i, img in enumerate(images):
# Convert image to final_mode if necessary
if img.mode != final_mode:
img = img.convert(final_mode)
x = (i % grid_size) * max_width
y = (i // grid_size) * max_height
concatenated_image.paste(img, (x, y))

# Save the concatenated image as PNG to support transparency if present
concatenated_image.save('/path/to/save_directory/concatenated_image.png')

print("Images have been concatenated into a grid and saved.")
```

Finally, I got the image! I was very excited to open it and get my flag when-

*Y DO ME LIKE THAT BRO?*

Who said it was going to be easy? After running into this, I tried lots of tools. Strings, cat, exiftool, etc. But to no avail. Now, given that this is a forensics challenge, and we have a .png on our hands, I decided to start testing out the standard steganography tools just to be safe. I downloaded and ran Stegsolve using the command I will never remember and will always google -> [*java -jar stegsolve.jar*]. Once it’s open, I opened the image in there and started swiping filters.

Quick question, how long would you take seeing shit like this before giving up and deciding to go back to your ancestor’s green-fields to plant, live under the sun, and never touch an electronic device again?

*When you leave the microwave on for more than 3 minutes.*

Honestly, not too many, I’d say. So, after two or three minutes of clicking next, I was thinking maybe this is a dead end, maybe I should try another challenge… and before I finished that thought, I was finally greeted with this.

*1_Th0ught_1'd_KMS :D*

Voila! By the time I did succeeded in cracking this one, and because the electricity support wasn’t the best and I had to sit in another room with stable electric flow, I was texting my team members letting them know that I got this when they told me they’d gotten more than 4–5 challenges. I was thrilled, proud, and mostly just in awe of how amazing these guys are.

---
