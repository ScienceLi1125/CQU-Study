import axios from 'axios';
import { Toast } from "vant"
import router from "@/router"

  //AXIOS拦截器,用于全局401清除缓存并跳转登陆页面

  const success_response = function (response) {
    // 2xx 范围内的状态码都会触发该函数。
    // 对响应数据做点什么
    return response;
  }

  const failure_response = function (error) {
    // 超出 2xx 范围的状态码都会触发该函数。
    // 对响应错误做点什么
    if (error.response.status === 401) {
      Toast.fail("登录已失效")
      localStorage.clear()
      router.replace({path:'/login'})
    }
    return Promise.reject(error);
  }


//统一Axios请求配置
function apiAxios(axiosConfig) {
    const service = axios.create({
      baseURL: 'https://app.randeweb.cn/api', // 设置统一的请求前缀
      timeout: 10000, // 设置统一的超时时长
      headers: {
        'Authorization': `Bearer ${localStorage._authing_token}`
      }
    });
    service.interceptors.response.use(success_response,failure_response)
    return service(axiosConfig)
  }
  
  export default apiAxios;

