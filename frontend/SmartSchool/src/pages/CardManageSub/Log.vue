<script setup>
import axios from "axios";
</script>

<template>
  <div class="text-center">
    <div class="my-2">
      <input
        class="bg-gray-300 text-gray-800 font-bold px-4 h-8 placeholder-gray-50 text-center rounded"
        :placeholder="筛选词"
        @keyup.enter="getLogByGrep"
        v-model="grep_word"
      />
    </div>
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
          <th scope="col">时间</th>
          <th scope="col">操作</th>
          <th scope="col">状态</th>
          <th scope="col">信息</th>
          <th scope="col">其他</th>
          <th scope="col">其他</th>
          <th scope="col">其他</th>
        </tr>
      </thead>
      <tbody v-if="logs.slice(start, start + log_per_page)!=[]">
        <tr v-for="(log, index) in logs.slice(start, start + log_per_page)" v-bind:key="log">
          <th scope="row">{{ start + index + 1 }}</th>
          <td>{{ log.split(" ").filter((i) => i)[0] }}</td>
          <td>{{ log.split(" ").filter((i) => i)[1] }}</td>
          <td>{{ log.split(" ").filter((i) => i)[2] }}</td>
          <td>
            {{
              log
                .split(" ")
                .filter((i) => i)[3]
                .split("|")[0]
            }}
          </td>
          <td
            v-for="(_log, index) in log
              .split(' ')
              .filter((i) => i)[3]
              .split('|')
              .slice(1)"
            v-bind:key="index"
           
          ><span>{{ _log }}</span>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
export default {
  data() {
    return {
      start: 0,
      log_per_page: 10,
      tips: "",
      _back_logs: [],
      logs: [],
      goto_page: "",
      grep_word: "",
    };
  },
  methods: {
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
    getLogByGrep(){
      axios
        .get("http://localhost:8000/GetLog/"+this.grep_word)
        .then((res) => {
          this._back_logs = res.data.split("\n").slice(0, -1);
          this.logs = this._back_logs;
          this.tips =
            "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
          this.start = 0;
        })
        .catch((err) => {
          console.log(err);
        });
    },
    getFullLog() {
      axios
        .get("http://localhost:8000/GetFullLog")
        .then((res) => {
          this._back_logs = res.data.split("\n").slice(0, -1);
          this.logs = this._back_logs;
          this.tips =
            "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
        })
        .catch((err) => {
          console.log(err);
        });
    },
  },
  beforeUpdate() {
    try {
      console.log(this.logs.slice(this.start, this.start + this.log_per_page));
    } catch (error) {
      console.log(error);
    }
    
  },
  async mounted() {
    await axios
      .get("http://localhost:8000/GetFullLog")
      .then((res) => {
        this._back_logs = res.data.split("\n").slice(0, -1);
        this.logs = this._back_logs;
        this.tips =
          "第" + (this.start / this.log_per_page + 1) + "/" + Math.ceil(this.logs.length / this.log_per_page) + "页";
      })
      .catch((err) => {
        console.log(err);
      });
  },
};
</script>
<style></style>
