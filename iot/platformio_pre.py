import shutil
import os

src = "lib/config_default.h"
dst = "lib/config.h"
if not os.path.exists(dst):
    shutil.copyfile(src, dst)
    

