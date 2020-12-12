import sys, pyperclip

def break_by_cr(text, prefix):
  
    lines = text.split("\\r\\n")

    for i in range(len(lines)):
        lines[i] = prefix + lines[i]

    text = '\n'.join(lines)

    return text


if __name__ == '__main__':
    prefix = ""
    if len(sys.argv) > 1:
        prefix = sys.argv[1]
    
    text = pyperclip.paste()
    print("copied text to clipboard:\n{}\n{}\n".format('-'*20,text))
    text = break_by_cr(text, prefix)
    print("copied text from clipboard:\n{}\n{}\n".format('-'*20,text))
