<script setup></script>

<template>
  <section class="text-gray-600 body-font">
    <div class="container px-5 py-24 mx-auto select-none">
      <div class="text-center mb-12">
        <h1 class="sm:text-3xl text-2xl font-medium title-font text-gray-900 mb-4">智慧校园卡管理平台</h1>
        <div class="flex mt-6 justify-center">
          <div class="w-16 h-1 rounded-full bg-indigo-500 inline-flex"></div>
        </div>
      </div>
      <div class="flex flex-wrap items-center text-center justify-center select-none">
        <div class="p-4 mx-10 flex flex-col text-center items-center cursor-pointer" @click="CardManageClicked">
          <div
            class="w-20 h-20 inline-flex items-center justify-center rounded-full bg-indigo-100 text-indigo-500 mb-5 flex-shrink-0"
          >
            <svg
              fill="none"
              stroke="currentColor"
              stroke-linecap="round"
              stroke-linejoin="round"
              stroke-width="2"
              class="w-10 h-10"
              viewBox="0 0 24 24"
            >
              <path d="M20 21v-2a4 4 0 00-4-4H8a4 4 0 00-4 4v2"></path>
              <circle cx="12" cy="7" r="4"></circle>
            </svg>
          </div>

          <div class="flex-grow">
            <h2 class="text-gray-900 text-lg title-font font-medium mb-3">卡片管理</h2>
            <p class="leading-relaxed text-base">校园卡管理</p>
          </div>
        </div>
        <div class="p-4 mx-10 flex flex-col text-center items-center cursor-pointer" @click="AnalysisClicked">
          <div
            class="w-20 h-20 inline-flex items-center justify-center rounded-full bg-indigo-100 text-indigo-500 mb-5 flex-shrink-0"
          >
            <svg
              fill="none"
              stroke="currentColor"
              stroke-linecap="round"
              stroke-linejoin="round"
              stroke-width="2"
              class="w-10 h-10"
              viewBox="0 0 24 24"
            >
              <circle cx="6" cy="6" r="3"></circle>
              <circle cx="6" cy="18" r="3"></circle>
              <path d="M20 4L8.12 15.88M14.47 14.48L20 20M8.12 8.12L12 12"></path>
            </svg>
          </div>
          <div class="flex-grow">
            <h2 class="text-gray-900 text-lg title-font font-medium mb-3">汇总分析</h2>
            <p class="leading-relaxed text-base">消费记录查询</p>
          </div>
        </div>
        <div class="p-4 mx-10 flex flex-col text-center items-center cursor-pointer" @click="ClientClicked">
          <div
            class="w-20 h-20 inline-flex items-center justify-center rounded-full bg-indigo-100 text-indigo-500 mb-5 flex-shrink-0"
          >
            <svg
              fill="none"
              stroke="currentColor"
              stroke-linecap="round"
              stroke-linejoin="round"
              stroke-width="2"
              class="w-10 h-10"
              viewBox="0 0 24 24"
            >
              <path d="M22 12h-4l-3 9L9 3l-3 9H2"></path>
            </svg>
          </div>
          <div class="flex-grow">
            <h2 class="text-gray-900 text-lg title-font font-medium mb-3">食堂应用</h2>
            <p class="leading-relaxed text-base">收费设备使用</p>
          </div>
        </div>
      </div>
    </div>
  </section>
</template>

<style scoped></style>

<script>
export default {
  methods: {
    CardManageClicked() {
      this.$router.push("/card_manage");
    },
    AnalysisClicked() {
      this.$router.push("/analysis");
    },
    ClientClicked() {
      this.$router.push("/client");
    },
  },
};
</script>
