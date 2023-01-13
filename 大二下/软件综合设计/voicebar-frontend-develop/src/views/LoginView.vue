<template>
  <div class="guard-container">
    <div id="guard">
      <!-- Authing提供的Guard组件 -->
      <Guard class="guard-component" :appId="appId" :config="guard_config" @login="onLogin" @register="onRegister"></Guard>
    </div>
  </div>
</template>

<script>
import { Guard } from "@authing/vue-ui-components";
import "@authing/vue-ui-components/lib/index.min.css";


export default {
  name: 'LoginView',
  data(){
    return {
      appId: "62de9dba412eabb062f40ab2",
      guard_config: {
        target: "#guard",
        autoRegister:true,
        disableRegister:false,
        contentCss:".g2-view-container {margin: 0 auto;background-color: #f7f8fa;} .g2-view-header > img { width:70px !important; height:70px !important; } .title {font-size:30px !important;}",
      },
    }
  },
  components: {
    Guard
  },
  computed: {
  },
  methods: { //登录或注册后,localStorage中就有了user的信息,可直接跳转至主页,让主页组件读取信息
    onLogin() {
      this.$router.replace({path:'/'})
    },
    onRegister() {
      this.$router.replace({path:'/'})
    }
  }
}
</script>

<style scoped lang="scss">
  .guard-container {
    padding-top: 20%;
  }
</style>