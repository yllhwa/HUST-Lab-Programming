<script setup>
import moment from "moment";
import axios from "axios";
</script>

<template>
  <section class="text-gray-600 body-font relative">
    <div class="container px-5 py-5 mx-auto">
      <div class="flex flex-col text-center w-full mb-5">
        <h1 class="sm:text-3xl text-2xl font-medium title-font mb-4 text-gray-900">食堂应用</h1>
      </div>
      <div class="lg:w-1/2 md:w-2/3 mx-auto">
        <div class="flex flex-wrap -m-2">
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="window_id" class="leading-7 text-sm text-gray-600">窗口号</label>
              <select
                v-model="window_id"
                id="window_id"
                @change="GetWindowLog"
                class="w-full rounded border appearance-none border-gray-300 py-2 focus:outline-none focus:ring-2 focus:ring-indigo-200 focus:border-indigo-500 text-base pl-3 pr-10"
              >
                <option v-for="i in 99" v-bind:key="i">{{ i }}</option>
              </select>
              <span
                class="absolute right-0 top-3 h-full w-10 text-center text-gray-600 pointer-events-none flex items-center justify-center"
              >
                <svg
                  fill="none"
                  stroke="currentColor"
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  stroke-width="2"
                  class="w-4 h-4"
                  viewBox="0 0 24 24"
                >
                  <path d="M6 9l6 6 6-6"></path>
                </svg>
              </span>
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="current_time" class="leading-7 text-sm text-gray-600">当前时间</label>
              <input
                type="text"
                id="current_time"
                name="current_time"
                v-model="current_time"
                @keyup.enter="GetWindowLog"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="card_id" class="leading-7 text-sm text-gray-600">卡号</label>
              <input
                type="text"
                id="card_id"
                name="card_id"
                v-model="card_id"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="money" class="leading-7 text-sm text-gray-600">金额</label>
              <input
                type="text"
                id="money"
                name="money"
                v-model="money"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="money" class="leading-7 text-sm text-gray-600">密码</label>
              <input
                type="password"
                id="password"
                name="password"
                v-model="password"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="card_id" class="leading-7 text-sm text-gray-600">今日消费条数</label>
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
              <label for="card_id" class="leading-7 text-sm text-gray-600">今日消费金额</label>
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
          <div class="p-2 w-full">
            <button
              class="flex mx-auto text-white bg-indigo-500 border-0 mt-6 py-2 px-8 focus:outline-none hover:bg-indigo-600 rounded text-lg"
              @click="Pay()"
            >
              消费
            </button>
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
            </tr>
          </thead>
          <tbody>
            <tr v-for="(log, index) in logs.slice(start, start + log_per_page)" v-bind:key="log">
              <th scope="row">{{ start + index + 1 }}</th>
              <td>{{ log.split("|")[0] }}</td>
              <td>{{ parseInt(log.split("|")[1])/100 }}</td>
              <td>{{ log.split("|")[2] }}</td>
              <td>{{ parseInt(log.split("|")[3])/100 }}</td>
              <td>{{ log.split("|")[4] }}</td>
              <td>{{ log.split("|")[5] }}</td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </section>
</template>

<script>
export default {
  data() {
    return {
      window_id: 1,
      card_id: "",
      money: 0,
      password: "",
      current_time: "",
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
    Pay() {
      axios
        .post("http://localhost:8000/Pay", {
          window_id: this.window_id,
          card_id: this.card_id,
          date: this.current_time.slice(0, 8),
          time: this.current_time.slice(8),
          money: this.money,
          password: this.password,
        })
        .then((res) => {
          if (res.data == "0") {
            alert("消费成功");
          } else if(res.data=="8888"){
            alert("请输入正确的密码");
          } 
          else {
            var error = res.data;
            if (res.data == "1") {
              // error = "学号重复";
            }
            alert("消费失败 " + error);
          }
          this.GetWindowLog();
        })
        .catch((err) => {
          alert(err);
        });
    },
    GetWindowLog() {
      axios
        .get("http://localhost:8000/GetWindowLog/" + this.window_id.toString())
        .then((res) => {
          this.logs = res.data.split("\n").slice(0, -1);
          this.start = 0;
          this.tips =
            "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
          var _pay_num = 0;
          var _pay_money = 0;
          for(var i = 0; i < this.logs.length; i++) {
            if(this.logs[i].split("|")[4] == this.current_time.slice(0, 8) && this.logs[i].split("|")[2] == "0") {
              _pay_num++;
              _pay_money += parseInt(this.logs[i].split("|")[1]);
              
            }
          }
          this.today_pay_num = _pay_num;
          this.today_pay_money = _pay_money/100;
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
