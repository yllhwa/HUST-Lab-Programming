import ctypes
# lib = ctypes.cdll.LoadLibrary("./SmartCardManager.dll")
lib = ctypes.cdll.LoadLibrary("C:\\Users\\yllhwa\\Desktop\\ProjectDesign\\backend\\SmartCardManager\\cmake-build-release-visual-studio\\Release\\SmartCardManager.dll")
# lib = ctypes.cdll.LoadLibrary("C:\\Users\\yllhwa\\Desktop\\ProjectDesign\\backend\\SmartCardManager\\cmake-build-debug-visual-studio\\Debug\\SmartCardManager.dll")


def CreateAccount(stu_id: str, stu_name: str, valid_date: str, time:str) -> int:
    """
    @des: 创建账户
    @param stu_id 学号
    @param stu_name 学生姓名
    @param valid_date 过期时间
    @ret: 状态码
    """
    return lib.CreateAccount(stu_id.encode(), stu_name.encode(), valid_date.encode(), time.encode())


def CreateCard(stu_id: str, time: str) -> int:
    """
    @des: 发卡
    @param stu_id 学号
    @ret: 状态码
    """
    return lib.CreateCard(stu_id.encode(), time.encode())


def DeleteAccount(stu_id: str, time: str) -> int:
    """
    @des: 删除账户
    @param stu_id 学号
    @ret: 状态码
    """
    return lib.DeleteAccount(stu_id.encode(), time.encode())


def LockAccount(stu_id: str, time:str) -> int:
    """
    @des: 锁定账户(挂失)
    @param stu_id 学号
    @ret: 状态码
    """
    return lib.LockAccount(stu_id.encode(), time.encode())


def UnLockAccount(stu_id: str, time:str) -> int:
    """
    @des: 解锁账户(解挂)
    @param stu_id 学号
    @ret: 状态码
    """
    return lib.UnLockAccount(stu_id.encode(), time.encode())


def ChargeMoney(stu_id: str, new_money: int, time: str) -> int:
    """
    @des: 为账户充值
    @param stu_id 学号
    @param new_money 充值的金额
    @ret: 状态码
    """
    return lib.ChargeMoney(stu_id.encode(), new_money, time.encode())


class StructPointer(ctypes.Structure):
    _fields_ = [("stu_id", ctypes.c_char_p), ("stu_name", ctypes.c_char_p),
                ("valid_date", ctypes.c_char_p), ("money", ctypes.c_int), ("status", ctypes.c_int)]


lib.GetInfoByStuId.restype = ctypes.POINTER(StructPointer)


def GetInfoByStuId(stu_id: str):
    """
    @des: 通过学号获取账户信息
    @param stu_id 学号
    @ret: 账户信息
    """
    return lib.GetInfoByStuId(stu_id.encode())


lib.SearchByStuId.restype = ctypes.POINTER(ctypes.c_char)


def SearchByStuId(stu_id: str):
    """
    @des: 通过学号模糊搜索学号
    @param stu_id 学号搜索字符串
    @ret: 学号信息
    """
    return lib.SearchByStuId(stu_id.encode())


def registerPos(pos_id:int, current_log_size:int)->int:
    return lib.registerPos(pos_id, current_log_size)

# lib.Pay.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_double]
def Pay(pos_id:int, card_id:str, date:str, time:str, amount:int, password:str)->int:
    return lib.Pay(pos_id, card_id.encode(), date.encode(), time.encode(), amount, password.encode())

lib.GetLog.restype = ctypes.POINTER(ctypes.c_char)
def GetLog(pos_id:int, size:int):
    return lib.GetLog(pos_id, size)

def get_string_from_pointer(pointer):
    str_list = []
    i = 0
    while(1):
        current = pointer[i]
        if (current==b"\0"):
            break
        str_list.append(current.decode())
        i += 1
    return "".join(str_list)[:-1]


def LibFree(ptr):
    lib.m_free(ptr)

def loadAll():
    lib.loadAll()

def _flush():
    lib._flush()


def analyzer_merge(sort_by:int)->int:
    return lib.analyzer_merge(sort_by)

# lib.get_merge_data_by_stu_id.argtypes = [ctypes.c_char_p]
def get_merge_data_by_stu_id(stu_id:str):
    return lib.get_merge_data_by_stu_id(stu_id.encode())

def get_merge_data_by_stu_name(stu_name:str):
    return lib.get_merge_data_by_stu_name(stu_name.encode())

def get_merge_data_by_date_range(start_date:str, end_date:str):
    return lib.get_merge_data_by_date_range(start_date.encode(), end_date.encode())

lib.find_friends.restype = ctypes.POINTER(ctypes.c_char)
def find_friends(stu_id:str):
    return lib.find_friends(stu_id.encode())

if __name__ == "__main__":
    loadAll()
    import time
    start = time.time()
    stu_str = find_friends("2020610107")
    print(time.time()-start)
    string = get_string_from_pointer(stu_str)
    string = string.split("|")
    string = [int(i) for i in string]
    # string.sort()
    print(string)
    LibFree(stu_str)
    # analyzer_merge(0)
    # import time
    # start = time.time()
    # get_merge_data_by_stu_id("20203802*")
    # print(time.time()-start)
    # print(1)