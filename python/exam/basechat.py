class ChatRoom:
    """Chat room example"""
    
    rooms = {}
    
    def __init__(self, name):
        self.name = name
        self.users = []
        self.messages =[]
        ChatRoom.rooms[name] = self
    
    def addSubscriber(self, subscriber):
        self.users.append(subscriber)
        subscriber.sendMessage(self.name, "User %s has entered." % subscriber.username)
        
    def removeSubscriber(self, subscriber)
        if subscriber in self.users:
            subscriber.sendMessage(self.name, "User %s is leaving." % subscriber.username)
            self.users.remove(subscriber)
    
    def addMessage(self, msg):
        self.messages.append(msg)
        
    def printMessage(self, out)
        print>>out, "Chat Transcript for: %s" % self.name
        for i in self.messages:
            print>>out, i
