class Dictionary:

    def __init__(self):
        self.words = set()

    # Load words in dictionary
    def load(self, dictionary):
        file = open(dictionary, "r")
        for line in file:
            self.words.add(line.rstrip("\n"))
        file.close()
        return True


    def check(self, word):
        if word.lower() in self.words:
            return True
        else:
            return False

    def size(self):
        return len(self.words)

    def unload(self):
        return True