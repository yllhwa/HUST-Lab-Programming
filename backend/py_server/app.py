from tracemalloc import start
from flask import Flask, request, jsonify, send_file
from flask_cors import CORS
import time
from bridge import CreateAccount, DeleteAccount, CreateCard, LockAccount, UnLockAccount, ChargeMoney, GetInfoByStuId, loadAll, SearchByStuId, get_string_from_pointer, LibFree, _flush, GetLog, Pay, analyzer_merge, get_merge_data_by_stu_id, get_merge_data_by_stu_name, get_merge_data_by_date_range
from bridge import find_friends

app = Flask(__name__)
CORS(app, supports_credentials=True)


@app.route('/', methods=['GET', 'POST'])
def hello_world():
    return 'Test WebServer'


@app.route('/CreateAccount', methods=['POST'])
def route_create_account():
    data = request.get_json()
    stu_id = data['stu_id']
    stu_name = data['stu_name']
    valid_date = data['valid_time']
    time = data['current_time']
    ret = str(CreateAccount(stu_id, stu_name, valid_date, time))
    return ret


@app.route("/DeleteAccount", methods=['POST'])
def route_delete_account():
    data = request.get_json()
    stu_id = data['stu_id']
    time = data['current_time']
    ret = str(DeleteAccount(stu_id, time))
    return ret


@app.route("/CreateCard", methods=['POST'])
def route_create_card():
    data = request.get_json()
    stu_id = data['stu_id']
    time = data['current_time']
    ret = str(CreateCard(stu_id, time))
    return ret


@app.route("/LockAccount", methods=['POST'])
def route_lock_account():
    data = request.get_json()
    stu_id = data['stu_id']
    time = data['current_time']
    ret = str(LockAccount(stu_id, time))
    return ret


@app.route("/UnLockAccount", methods=['POST'])
def route_unlock_account():
    data = request.get_json()
    stu_id = data['stu_id']
    time = data['current_time']
    ret = str(UnLockAccount(stu_id, time))
    return ret


@app.route("/ChargeMoney", methods=['POST'])
def route_charge_money():
    data = request.get_json()
    stu_id = data['stu_id']
    new_money = int(data['new_money'])*100
    time = data['current_time']
    ret = str(ChargeMoney(stu_id, new_money, time))
    return ret


@app.route("/GetInfoByStuId", methods=['POST'])
def route_get_info_by_stu_id():
    data = request.get_json()
    stu_id = data['stu_id']
    info = GetInfoByStuId(stu_id)
    ret = {
        "stu_name": info.contents.stu_name.decode(), 
        "money": info.contents.money/100,
        "valid_date": info.contents.valid_date.decode(),
        "status": info.contents.status
        }
    return jsonify(ret)

@app.route("/BatchOperation", methods=['POST'])
def route_batch_operation():
    loadAll()
    return "Batch Operation Success"

@app.route("/FuzzyQuery", methods=['POST'])
def route_fuzzy_query():
    data = request.get_json()
    stu_id = data['stu_id']
    info_p = SearchByStuId(stu_id)
    info = get_string_from_pointer(info_p)
    LibFree(info_p)
    return info

@app.route("/GetFullLog", methods=['GET', 'POST'])
def route_get_log():
    _flush()
    return send_file('CardManageLog.txt')

@app.route("/GetLog/<grep_str>", methods=['GET', 'POST'])
def route_get_log_with_grep(grep_str):
    print(grep_str)
    _flush()
    with open('CardManageLog.txt', 'r', encoding="utf-8") as f:
        with open("CardManageLog_grep.txt", "w", encoding="utf-8") as f_grep:
            for line in f:
                if grep_str in line:
                    f_grep.write(line)
            f_grep.close()
            return send_file('CardManageLog_grep.txt')

@app.route("/GetWindowLog/<window_id>" , methods=['GET', 'POST'])
def route_get_window_log(window_id):
    string = GetLog(int(window_id), 60000)
    with open(f"window_logs/pos{window_id}.txt", "w", encoding="utf-8") as f:
        f.write(get_string_from_pointer(string))
        f.write("\n")
    LibFree(string)
    return send_file(f"window_logs/pos{window_id}.txt")

@app.route("/Pay", methods=['POST'])
def route_pay():
    data = request.get_json()
    window_id = int(data['window_id'])
    card_id = data['card_id']
    date = data['date']
    time = data['time']
    password = data['password']
    money = int(float(data['money'])*100)
    ret = str(Pay(window_id, card_id, date, time, money, password))
    return ret

@app.route("/GetAnalyzerMergeData", methods=['GET'])
def route_get_analyzer_merge_data():
    analyzer_merge(0)
    return send_file("analyze_merge.txt")

@app.route("/GetAnalyzerMergeDataByStuId", methods=[ 'POST'])
def route_get_analyzer_merge_data_by_stu_id():
    data = request.get_json()
    stu_id = data['stu_id']
    start = time.time()
    get_merge_data_by_stu_id(stu_id)
    print(time.time() - start)
    return send_file("analyze_merge_by_stu_id.txt")

@app.route("/GetAnalyzerMergeDataByStuName", methods=[ 'POST'])
def route_get_analyzer_merge_data_by_stu_name():
    data = request.get_json()
    stu_name = data['stu_name']
    start = time.time()
    get_merge_data_by_stu_name(stu_name)
    print(time.time() - start)
    return send_file("analyze_merge_by_stu_name.txt")

@app.route("/GetAnalyzerMergeDataByDateRange", methods=[ 'POST'])
def route_get_analyzer_merge_data_by_date_range():
    data = request.get_json()
    start_date = data['start_date']
    end_date = data['end_date']
    start = time.time()
    get_merge_data_by_date_range(start_date, end_date)
    print(time.time() - start)
    return send_file("analyze_merge_by_date_range.txt")

@app.route("/FindFriends", methods=[ 'POST'])
def route_find_friends():
    data = request.get_json()
    stu_id = data['stu_id']
    str_p = find_friends(stu_id)
    friends_str = get_string_from_pointer(str_p)
    LibFree(str_p)
    return friends_str

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
