<script setup>
import moment from "moment";
import axios from "axios";
</script>

<template>
  <section class="text-gray-600 body-font relative">
    <div class="container px-5 py-5 mx-auto">
      <div class="flex flex-col text-center w-full mb-5">
        <h1 class="sm:text-3xl text-2xl font-medium title-font mb-4 text-gray-900">汇总分析</h1>
      </div>
      <div class="lg:w-1/2 md:w-2/3 mx-auto">
        <div class="flex flex-wrap -m-2">
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="stu_id" class="leading-7 text-sm text-gray-600">学号模糊查询</label>
              <input
                type="text"
                id="stu_id"
                name="stu_id"
                v-model="stu_id"
                @keyup.enter="SearchStuId"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="stu_name" class="leading-7 text-sm text-gray-600">姓名模糊查询</label>
              <input
                type="text"
                id="stu_name"
                name="stu_name"
                v-model="stu_name"
                @keyup.enter="SearchStuName"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="money" class="leading-7 text-sm text-gray-600">起止日期</label>
              <Datepicker v-model="date_range" @update:model-value="onDateChange" range />
            </div>
          </div>
          <div class="p-2 w-1/2"></div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="card_id" class="leading-7 text-sm text-gray-600">消费条数</label>
              <input
                type="text"
                id="today_pay_num"
                name="today_pay_num"
                v-model="today_pay_num"
                disabled
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="card_id" class="leading-7 text-sm text-gray-600">消费金额</label>
              <input
                type="text"
                id="today_pay_money"
                name="today_pay_money"
                v-model="today_pay_money"
                disabled
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
        </div>
      </div>
      <div class="text-center mt-4">
        <!-- <div class="my-2">
          <input
            class="bg-gray-300 text-gray-800 font-bold px-4 h-8 placeholder-gray-50 text-center rounded"
            :placeholder="筛选词"
            @keyup.enter="getLogByGrep"
            v-model="grep_word"
          />
        </div> -->
        <div class="inline-flex my-2">
          <button class="bg-gray-300 hover:bg-gray-400 text-gray-800 font-bold py-2 px-4 rounded-l" @click="prev">
            上一页
          </button>
          <input
            class="bg-gray-300 text-gray-800 font-bold px-4 placeholder-gray-50 text-center"
            :placeholder="tips"
            @keyup.enter="goto"
            v-model="goto_page"
          />

          <button class="bg-gray-300 hover:bg-gray-400 text-gray-800 font-bold py-2 px-4 rounded-r" @click="next">
            下一页
          </button>
        </div>
        <table class="table">
          <thead>
            <tr>
              <th scope="col">#</th>
              <th scope="col">卡号</th>
              <th scope="col">金额</th>
              <th scope="col">状态码</th>
              <th scope="col">余额</th>
              <th scope="col">日期</th>
              <th scope="col">时间</th>
              <th scope="col">学号</th>
              <th scope="col">姓名</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(log, index) in logs.slice(start, start + log_per_page)" v-bind:key="log">
              <th scope="row">{{ start + index + 1 }}</th>
              <td>{{ log.split("|")[0] }}</td>
              <td>{{ parseInt(log.split("|")[1]) / 100 }}</td>
              <td>{{ log.split("|")[2] }}</td>
              <td>{{ parseInt(log.split("|")[3]) / 100 }}</td>
              <td>{{ log.split("|")[4] }}</td>
              <td>{{ log.split("|")[5] }}</td>
              <td>{{ log.split("|")[6] }}</td>
              <td>{{ log.split("|")[7] }}</td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </section>
</template>

<script>
import Datepicker from "vue3-date-time-picker";
import "vue3-date-time-picker/dist/main.css";
import { toRaw } from "@vue/reactivity";
export default {
  components: {
    Datepicker,
  },
  data() {
    return {
      stu_id: "",
      stu_name: "",
      date_range: null,
      _back_logs: [],
      logs: [],
      start: 0,
      log_per_page: 10,
      tips: "",
      goto_page: "",
      grep_word: "",
      today_pay_num: 0,
      today_pay_money: 0,
    };
  },
  methods: {
    getCurrentTime() {
      return moment().format("YYYYMMDDHHmmssSS");
    },
    onDateChange() {
      // this.date_range[0].getYear();
      var date0 = toRaw(this.date_range[0]);
      var date1 = toRaw(this.date_range[1]);
      moment(date0).format("YYYYMMDD");
      axios
        .post("http://localhost:8000/GetAnalyzerMergeDataByDateRange", {
          start_date: moment(date0).format("YYYYMMDD"),
          end_date: moment(date1).format("YYYYMMDD"),
        })
        .then((res) => {
          this.logs = res.data.split("\n").slice(0, -1);
          this.start = 0;
          this.tips =
            "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
          var _pay_num = 0;
          var _pay_money = 0;
          for (var i = 0; i < this.logs.length; i++) {
            if (this.logs[i].split("|")[2] == "0") {
              _pay_num++;
              _pay_money += parseInt(this.logs[i].split("|")[1]);
            }
          }
          this.today_pay_num = _pay_num;
          this.today_pay_money = _pay_money / 100;
          alert("查询成功");
        });
      console.log(moment(date0).format("YYYYMMDD"), moment(date1).format("YYYYMMDD"));
    },

    SearchStuId() {
      axios.post("http://localhost:8000/GetAnalyzerMergeDataByStuId", { stu_id: this.stu_id }).then((res) => {
        this.logs = res.data.split("\n").slice(0, -1);
        this.start = 0;
        this.tips =
          "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
        var _pay_num = 0;
        var _pay_money = 0;
        for (var i = 0; i < this.logs.length; i++) {
          if (this.logs[i].split("|")[2] == "0") {
            _pay_num++;
            _pay_money += parseInt(this.logs[i].split("|")[1]);
          }
        }
        this.today_pay_num = _pay_num;
        this.today_pay_money = _pay_money / 100;
        alert("查询成功");
      });
    },
    SearchStuName() {
      axios.post("http://localhost:8000/GetAnalyzerMergeDataByStuName", { stu_name: this.stu_name }).then((res) => {
        this.logs = res.data.split("\n").slice(0, -1);
        this.start = 0;
        this.tips =
          "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
        var _pay_num = 0;
        var _pay_money = 0;
        for (var i = 0; i < this.logs.length; i++) {
          if (this.logs[i].split("|")[2] == "0") {
            _pay_num++;
            _pay_money += parseInt(this.logs[i].split("|")[1]);
          }
        }
        this.today_pay_num = _pay_num;
        this.today_pay_money = _pay_money / 100;
        alert("查询成功");
      });
    },
    GetWindowLog() {
      axios
        .get("http://localhost:8000/GetAnalyzerMergeData")
        .then((res) => {
          this._back_logs = res.data.split("\n").slice(0, -1);
          this.logs = this._back_logs;
          this.start = 0;
          this.tips =
            "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
          var _pay_num = 0;
          var _pay_money = 0;
          for (var i = 0; i < this.logs.length; i++) {
            if (this.logs[i].split("|")[2] == "0") {
              _pay_num++;
              _pay_money += parseInt(this.logs[i].split("|")[1]);
            }
          }
          this.today_pay_num = _pay_num;
          this.today_pay_money = _pay_money / 100;
          alert("获取成功");
        })
        .catch((err) => {
          alert(err);
        });
    },
    prev() {
      this.start -= this.log_per_page;
      this.tips =
        "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
    },
    next() {
      this.start += this.log_per_page;
      this.tips =
        "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
    },
    goto() {
      var goto_page_int = parseInt(this.goto_page);
      console.log(this.goto_page);
      this.start = (goto_page_int - 1) * this.log_per_page;
      this.tips = "第" + goto_page_int + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
      this.goto_page = "";
    },
  },
  mounted() {
    this.current_time = this.getCurrentTime();
    this.GetWindowLog();
  },
};
</script>
<style></style>
