import { AuthenticationClient } from "authing-js-sdk";
import { Toast } from "vant"
import router from "@/router"

export function getAuthClientWithToken(token) { //返回使用对应token的Authing客户端
    const authClient = new AuthenticationClient({
        appId: "62de9dba412eabb062f40ab2",
        token: token
      });
    return authClient
}

//true--已登录,false--未登录
export async function checkLoginStatus() {//参考Authing官网开发文档
    //从localStorage读取存储的用户信息
    const authClient = new AuthenticationClient({
        appId: "62de9dba412eabb062f40ab2",
      });
    const user = await authClient.getCurrentUser();
    if (user && user.token) {
        const { status } = await authClient.checkLoginStatus(user.token);
        return status
    }
}

export async function getLocalUser() { //获得本地Authing缓存用户
    const authClient = new AuthenticationClient({
        appId: "62de9dba412eabb062f40ab2",
      });
    return authClient.getCurrentUser();
}

export async function retrieveAuthingUser() {//从localStorage中恢复信息,并验证登录的有效性
  const authClient = new AuthenticationClient({
    appId: "62de9dba412eabb062f40ab2",
  });
  const user = await authClient.getCurrentUser();
  if (user && user.token) {
      const { status } = await authClient.checkLoginStatus(user.token);

      if (status) {
          return user
      } else {
        Toast.fail("登录已失效")
        router.replace({path:'/login'})
      }
  }
}