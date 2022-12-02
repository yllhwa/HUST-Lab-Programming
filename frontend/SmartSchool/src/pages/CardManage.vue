<script setup></script>

<template>
  <section class="text-gray-600 body-font">
    <div class="container px-5 py-8 mx-auto">
      <div class="flex flex-wrap -m-2">
        <div class="p-2 lg:w-1/3 md:w-1/2 w-full cursor-pointer" v-for="(func, index) in functions"  :key="index" @click="func.onclick">
          <div class="h-full flex items-center border-gray-200 border p-4 rounded-lg">
            <img
              alt="team"
              class="w-16 h-16 object-cover object-center flex-shrink-0 mr-4"
              :src="func.img"
            />
            <div class="flex-grow">
              <h2 class="text-gray-900 title-font text-xl">{{func.name}}</h2>
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
      functions: [
          {"name":"开户", "img":"img/开户.png", "onclick":this.开户},
          {"name":"销户", "img":"img/销户.png", "onclick":this.销户},
          {"name":"发卡", "img":"img/发卡.png", "onclick":this.发卡},
          {"name":"挂失", "img":"img/挂失.png", "onclick":this.挂失},
          {"name":"解挂", "img":"img/解挂.png", "onclick":this.解挂},
          {"name":"充值", "img":"img/充值.png", "onclick":this.充值},
          {"name":"查询账户", "img":"img/查询账户.png", "onclick":this.查询账户},
          {"name":"模糊查询", "img":"img/模糊查询.png", "onclick":this.模糊查询},
          {"name":"批量", "img":"img/批量.png", "onclick":this.批量},
          {"name":"日志", "img":"img/日志.png", "onclick":this.日志},
          {"name":"同伴查询", "img":"img/同伴查询.png", "onclick":this.同伴查询},
      ],
    };
  },
  methods: {
    开户() {
      this.$router.push("/card_manage/openAccount");
    },
    销户() {
      this.$router.push("/card_manage/delAccount");
    },
    发卡() {
      this.$router.push("/card_manage/createCard");
    },
    挂失() {
      this.$router.push("/card_manage/lockAccount");
    },
    解挂() {
      this.$router.push("/card_manage/UnLockAccount");
    },
    充值() {
      this.$router.push("/card_manage/ChargeMoney");
    },
    查询账户() {
      this.$router.push("/card_manage/GetInfoByStuId");
    },
    模糊查询() {
      this.$router.push("/card_manage/FuzzyQuery");
    },
    批量() {
      this.$router.push("/card_manage/BatchOperation");
    },
    日志() {
      this.$router.push("/card_manage/Log");
    },
    同伴查询(){
      this.$router.push("/card_manage/FindFriends");
    }
  },
};
</script>
<style></style>
