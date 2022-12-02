<script setup>
import moment from "moment";
import axios from "axios";
</script>

<template>
  <section class="text-gray-600 body-font relative">
    <div class="container px-5 py-5 mx-auto">
      <div class="flex flex-col text-center w-full mb-5">
        <h1 class="sm:text-3xl text-2xl font-medium title-font mb-4 text-gray-900">同伴查询</h1>
      </div>
      <div class="lg:w-1/2 md:w-2/3 mx-auto">
        <div class="flex flex-wrap -m-2">
          <div class="p-2 w-full">
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
          <div class="p-2 w-full">
            <button
              class="flex mx-auto text-white bg-indigo-500 border-0 mt-6 py-2 px-8 focus:outline-none hover:bg-indigo-600 rounded text-lg"
              @click="createCard()"
            >
              查询
            </button>
          </div>
          <div class="p-2 w-full">
            <div class="relative text-center">
                <p class="font-black text-xl">学号</p>
                <p v-for="stu_id in stu_id_list" v-bind:key="stu_id">{{stu_id}}</p>
            </div>
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
      stu_id_list: [],
    };
  },
  methods: {
    getCurrentTime() {
      return moment().format("YYYYMMDD");
    },
    createCard() {
      axios
        .post("http://localhost:8000/FindFriends", {
          stu_id: this.stu_id,
        })
        .then((res) => {
            res.data = res.data.toString();
            this.stu_id_list = res.data.split('|');
        })
        .catch((err) => {
          alert(err);
        });
    },
  },
  mounted() {
    this.current_time = this.getCurrentTime();
  },
};
</script>
<style></style>
