import os
import searchfile



if __name__ == "__main__":
    searchfile.search_file(".*py$", ".", searchfile.print_file)