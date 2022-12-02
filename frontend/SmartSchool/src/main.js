import { createApp, h } from "vue";
import App from "./App.vue";
import { createRouter, createWebHistory } from "vue-router";
import Main from "./pages/Main.vue";
import CardManage from "./pages/CardManage.vue";
import Analysis from "./pages/Analysis.vue"
import Client from "./pages/Client.vue"
import OpenAccount from "./pages/CardManageSub/OpenAccount.vue"
import DeleteAccount from "./pages/CardManageSub/DeleteAccount.vue"
import CreateCard from "./pages/CardManageSub/CreateCard.vue"
import LockAccount from "./pages/CardManageSub/LockAccount.vue"
import UnLockAccount from "./pages/CardManageSub/UnLockAccount.vue"
import ChargeMoney from "./pages/CardManageSub/ChargeMoney.vue"
import GetInfoByStuId from "./pages/CardManageSub/GetInfoByStuId.vue"
import BatchOperation from "./pages/CardManageSub/BatchOperation.vue"
import FuzzyQuery from "./pages/CardManageSub/FuzzyQuery.vue"
import Log from "./pages/CardManageSub/Log.vue"
import FindFriends from "./pages/CardManageSub/FindFriends.vue"
import "./assets/main.css";
const routes = [
  {
    path: "/",
    component: Main,
  },
  {
    path: "/card_manage",
    component: CardManage,
  },
  {
    path: "/analysis",
    component: Analysis,
  },
  {
    path: "/client",
    component: Client,
  },
  {
    path: "/card_manage/openAccount",
    component: OpenAccount,
  },
  {
    path: "/card_manage/delAccount",
    component: DeleteAccount,
  },
  {
    path: "/card_manage/createCard",
    component: CreateCard,
  },
  {
    path: "/card_manage/lockAccount",
    component: LockAccount,
  },
  {
    path: "/card_manage/unLockAccount",
    component: UnLockAccount,
  },
  {
    path: "/card_manage/chargeMoney",
    component: ChargeMoney,
  },
  {
    path: "/card_manage/GetInfoByStuId",
    component: GetInfoByStuId,
  },
  {
    path: "/card_manage/BatchOperation",
    component: BatchOperation,
  },
  {
    path: "/card_manage/FuzzyQuery",
    component: FuzzyQuery,
  },
  {
    path: "/card_manage/Log",
    component: Log,
  },
  {
    path: "/card_manage/FindFriends",
    component: FindFriends,
  }
];
const router = createRouter({
  history: createWebHistory(),
  routes: routes,
});
const app = createApp({
  render: () => h(App),
});
app.use(router);
app.mount("#app");
// createApp(App).mount("#app");
