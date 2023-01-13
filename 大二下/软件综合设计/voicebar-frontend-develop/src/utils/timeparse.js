import moment from 'moment'
//全局本地化
moment.locale("zh-CN");

//计算时间差
export function parseTime(time) {
    return moment(time).fromNow()
}