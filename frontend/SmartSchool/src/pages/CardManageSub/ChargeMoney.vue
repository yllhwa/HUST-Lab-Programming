<script setup>
import moment from "moment";
import axios from "axios";
</script>

<template>
  <section class="text-gray-600 body-font relative">
    <div class="container px-5 py-5 mx-auto">
      <div class="flex flex-col text-center w-full mb-5">
        <h1 class="sm:text-3xl text-2xl font-medium title-font mb-4 text-gray-900">充值</h1>
      </div>
      <div class="lg:w-1/2 md:w-2/3 mx-auto">
        <div class="flex flex-wrap -m-2">
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="stu_id" class="leading-7 text-sm text-gray-600">学号</label>
              <input
                type="text"
                id="stu_id"
                name="stu_id"
                v-model="stu_id"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="stu_name" class="leading-7 text-sm text-gray-600">金额</label>
              <input
                type="text"
                id="money"
                name="money"
                v-model="money"
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out"
              />
            </div>
          </div>
          <div class="p-2 w-1/2">
            <div class="relative">
              <label for="stu_name" class="leading-7 text-sm text-gray-600">姓名</label>
              <input
                type="text"
                id="stu_name"
                name="stu_name"
                v-model="stu_name"
                disabled
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out"
              />
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
                disabled
                class="w-full bg-gray-100 bg-opacity-50 rounded border border-gray-300 focus:border-indigo-500 focus:bg-white focus:ring-2 focus:ring-indigo-200 text-base outline-none text-gray-700 py-1 px-3 leading-8 transition-colors duration-200 ease-in-out cursor-default"
              />
            </div>
          </div>
          <div class="p-2 w-full">
            <button
              class="flex mx-auto text-white bg-indigo-500 border-0 mt-6 py-2 px-8 focus:outline-none hover:bg-indigo-600 rounded text-lg"
              @click="createCard()"
            >
              充值
            </button>
          </div>
        </div>
      </div>
    </div>
  </section>
</template>

<script>
export default {
  data() {
    return {
      stu_id: "",
      stu_name: "",
      money:"",
      current_time: "",
    };
  },
  methods: {
    getCurrentTime() {
      return moment().format("YYYYMMDD");
    },
    createCard(){
        axios.post("http://localhost:8000/ChargeMoney", {
            stu_id: this.stu_id,
            stu_name: this.stu_name,
            new_money: this.money,
            current_time: this.current_time,
        }).then(res => {
            if (res.data == "0") {
                alert("充值成功");
                this.$router.push("/card_manage");
            }
            else{
                var error = res.data;
                if (res.data=="1"){
                  error = "学号不存在";
                }
                else if(res.data=="2"){
                    error = "账户余额超限";
                }
                else if(res.data=="3"){
                    error = "账户非正常状态";
                }
                alert("充值失败 " + error);
            }
        }).catch(err => {
            alert(err);
        });
    }
  },
  mounted() {
    this.current_time = this.getCurrentTime();
  },
};
</script>
<style></style>
