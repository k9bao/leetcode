# 删除无效的文件及文件夹

import os
import re
import shutil


def del_files(path, listRegex):
    patten = []
    for v in listRegex:
        patten.append(re.compile(v))

    for root, dirs, files in os.walk(path):
        for name in dirs:
            for p in patten:
                if re.search(p, name):
                    print("Delete Dir: " + os.path.join(root, name))
                    shutil.rmtree(os.path.join(root, name))
        for name in files:
            for p in patten:
                if re.search(p, name):
                    print("Delete File: " + os.path.join(root, name))
                    os.remove(os.path.join(root, name))


if __name__ == "__main__":
    path = '..'
    # 1. 所有的a.out文件可以删除,c++目标文件
    # 2. 所有的a.out.dSYM文件夹可以删除，c++临时文件
    listRegex = ["^a.out*"]
    del_files(path, listRegex)
