from data.resources import resources


class Resource(object):
    def __init__(self, name, string, value, needs, rate):
        self.name = name
        self.string = string
        self.value = value
        self.needs = needs
        self.rate = rate
        self.stock = 10

    def __repr__(self):
        return self.name


def get_resources():
    instances = tuple(Resource(name=resource, **data)
                      for resource, data in resources.items())
    return instances
