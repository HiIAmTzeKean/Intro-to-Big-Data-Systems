import re
import sys
from pyspark import SparkConf, SparkContext
import time

# def normalizeWords(text):
#     return re.split('[\w]+', text)
def normalizeWords(text):
    return re.compile(r'\W+', re.UNICODE).split(text)

def process(inputRDD):
    words = inputRDD.flatMap(normalizeWords)
    wcPair = words.map(lambda s: (s,1))
    return wcPair.reduceByKey(lambda w1, w2:  w1 + w2)

if __name__ == '__main__':
    conf = SparkConf()
    sc = SparkContext(conf=conf)
    lines = sc.textFile(sys.argv[1])

    first = time.time()

    # Students: Implement Word Count!
    resultRDD = process(lines)
    results = resultRDD.sortBy(lambda x: x[1],False).collect()
    for i in range(10):
        print(results[i])
    # End of implementation
    last = time.time()
    print("Total program time: %.2f seconds" % (last - first))
    sc.stop()
