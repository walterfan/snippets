registry = []

def register(func):
	print("register function {}".format(func))
	registry.append(func)
	return func

@register
def hello():
	print("hello")

@register
def world():
	print("world")

if __name__ == '__main__':
	hello()
	world()
	for func in registry:
		print("there is a registered {}".format(func))