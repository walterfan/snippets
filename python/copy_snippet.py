getCurrentTimeStr = """
    def getCurrentTimeStr(fmtStr = '%Y%m%d%H%M'):
        now = datetime.datetime.now()
        #return "{}{}{}{}{}{}".format(now.year, now.month, now.day, now.hour, now.minute, now.second)
        return now.strftime(fmtStr)
    """

getTimeStr = """
    def getTimeStr(dayDelta = 0, fmtStr = '%Y-%m-%d %H:%M:%S', dt = None):
        if None == dt:
            dt = datetime.datetime.now()
        if dayDelta != 0:
            delta = datetime.timedelta(days = dayDelta)
            dt = dt + delta

        return dt.strftime(fmtStr)
    """
import sys, pyperclip

snippets = {
    "getTimeStr": getTimeStr,
    "getCurrentTimeStr": getCurrentTimeStr
}

if __name__ == '__main__':

    if len(sys.argv) < 2:
        print('usage: python copy_snippet tag - copy snippet to clipboard')
        sys.exit(1)

    snippet = sys.argv[1]

    if snippet in snippets:
        pyperclip.copy(snippets[snippet])
        print("snippet for {} copied to clipboard".format(snippet))
    else:
        print("snippet for {} copied is not found".format(snippet))

