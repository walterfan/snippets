from PIL import Image, ImageDraw

def drawrect(drawcontext, xy, outline=None, width=0):
    (x1, y1), (x2, y2) = xy
    points = (x1, y1), (x2, y1), (x2, y2), (x1, y2), (x1, y1)
    drawcontext.line(points, fill=outline, width=width)

im = Image.new("RGB", (250, 250), color="white")
ctx = ImageDraw.Draw(im)

drawrect(ctx, [(50, 50), (200, 200)], outline="blue", width=1)

im.show()