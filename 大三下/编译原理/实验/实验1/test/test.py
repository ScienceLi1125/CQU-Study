import sys,json
from build import build_compiler
from run import run_compiler
from score import score_compiler

assert(len(sys.argv) == 2)

step = "-" + sys.argv[1]
if step == "-s0":
    oftype = "tk"
elif step == "-s1":
    oftype = "json"
elif step == "-s2":
    oftype = "ir"
else:
    print("illegal input")
    exit()

print("------------ build_compiler ------------")
build_compiler()
print("------------  run_compiler  ------------")
run_compiler(sys.argv[1])
print("------------ score_compiler ------------")
score = score_compiler(sys.argv[1])

logfile = open("log.txt","w+")
sys.stdout = logfile
print(json.dumps({"score":str(score)}))
logfile.close()