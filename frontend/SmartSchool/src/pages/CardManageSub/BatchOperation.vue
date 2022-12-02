<script setup>
import moment from "moment";
import axios from "axios";
</script>

<template>
  <section class="text-gray-600 body-font relative">
    <div class="container px-5 py-5 mx-auto">
      <div class="flex flex-col text-center w-full mb-5">
        <h1 class="sm:text-3xl text-2xl font-medium title-font mb-4 text-gray-900">批量操作</h1>
      </div>
      <div class="lg:w-1/2 md:w-2/3 mx-auto">
        <div class="flex flex-wrap -m-2">
          <div class="p-2 w-full">
            <div class="relative">
              <ProgressBar :currentVal="val" :minVal="min" :maxVal="max" v-slot="{ percent }">
                进度 {{ percent }} %
              </ProgressBar>
            </div>
          </div>
          <div class="p-2 w-full">
            <button
              class="flex mx-auto text-white bg-indigo-500 border-0 mt-6 py-2 px-8 focus:outline-none hover:bg-indigo-600 rounded text-lg"
              @click="batchOperatiion()"
            >
              批量操作
            </button>
          </div>
        </div>
      </div>
    </div>
  </section>
</template>

<script>
import ProgressBar from "../../components/ProgressBar.vue";
export default {
  data() {
    return {
      min: 0,
      max: 100,
      val: 0,
      current_time: "",
    };
  },
  methods: {
    getCurrentTime() {
      return moment().format("YYYYMMDD");
    },
    updateProgress(){
        this.val = (this.val+30)>this.max?this.max:(this.val+30);
    },
    
    batchOperatiion() {
        setInterval(this.updateProgress,"1000");
      axios
        .post("http://localhost:8000/BatchOperation", {
          current_time: this.current_time,
        })
        .then((res) => {
          alert(res.data);
          this.val=this.max;
        })
        .catch((err) => {
          alert(err);
          this.val=this.max;
        });
        
    },
  },
  mounted() {
    this.current_time = this.getCurrentTime();
  },
  components: {
    ProgressBar,
  },
};
</script>
<style></style>
