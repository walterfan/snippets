import io
import os
import math
import sys
import numpy as np
from PIL import Image

def JPEGSaveWithTargetSize(im, filename, target):
   """Save the image as JPEG with the given name at best quality that makes less than "target" bytes"""
   # Min and Max quality
   Qmin, Qmax = 25, 96
   # Highest acceptable quality found
   Qacc = -1
   while Qmin <= Qmax:
      m = math.floor((Qmin + Qmax) / 2)

      # Encode into memory and get size
      buffer = io.BytesIO()
      im.save(buffer, format="JPEG", quality=m)
      s = buffer.getbuffer().nbytes

      if s <= target:
         Qacc = m
         Qmin = m + 1
      elif s > target:
         Qmax = m - 1

   # Write to disk at the defined quality
   if Qacc > -1:
      im.save(filename, format="JPEG", quality=Qacc)
   else:
      print("ERROR: No acceptble quality factor found", file=sys.stderr)

################################################################################
# main
################################################################################
if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('usage: python jpg_resize <origin_file> <target_size> - resize jpg file size')
        sys.exit(1)

    origin_file = sys.argv[1]
    target_size = int(sys.argv[2])
    target_file = "changed_" + os.path.basename(origin_file)

    im = Image.open(origin_file)
    print("change file size of {} to {} as {}".format(origin_file, target_file, target_size))
    # Save at best quality under 100,000 bytes
    JPEGSaveWithTargetSize(im, target_file, target_size)