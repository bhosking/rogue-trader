from source.resource import get_resources
from collections import Counter


class Town(object):
    def __init__(self):
        self.resources = get_resources()

    def get_stock(self):
        stock = Counter({res.name: res.stock for res in self.resources})
        return stock

    def tick(self, dt):
        stock = self.get_stock()
        create = Counter()
        for resource in self.resources:
            max_production = dt * resource.rate
            fill = [max_production]
            for need, amount in resource.needs.items():
                fill.append(stock[need] / amount)
            production = min(fill)
            if production:
                use = {need: amount * production
                       for need, amount in resource.needs.items()}
                stock.subtract(use)
                create[resource.name] = production
        stock += create
        self.set_stock(stock)

    def set_stock(self, stock):
        for resource in self.resources:
            resource.stock = stock[resource.name]

test_town = Town()
while True:
    test_town.tick(1)
