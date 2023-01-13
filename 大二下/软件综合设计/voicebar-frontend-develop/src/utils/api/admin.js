import apiAxios from "./axios"
import { Toast } from "vant"

//管理员删除用户
export async function deleteUser(user_id) {
    const task = apiAxios({
        url: `admin/${user_id}/delete/`,
        method: 'delete',
    })
    try {
        Toast.loading("删除用户中")
        await task
        Toast.clear()
        Toast.success("已删除用户")
    } catch(error) {
        Toast.clear()
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`删除用户失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//管理员封禁用户
export async function banUser(user_id) {
    const task = apiAxios({
        url: `admin/${user_id}/ban/`,
        method: 'post',
    })
    try {
        Toast.loading("封禁用户中")
        await task
        Toast.clear()
        Toast.success("已封禁用户")
    } catch(error) {
        Toast.clear()
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`封禁用户失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//管理员解封用户
export async function unbanUser(user_id) {
    const task = apiAxios({
        url: `admin/${user_id}/unban/`,
        method: 'post',
    })
    try {
        Toast.loading("解封用户中")
        await task
        Toast.clear()
        Toast.success("已解封用户")
    } catch(error) {
        Toast.clear()
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`解封用户失败${JSON.stringify(error.response.data)}`)
        }
    }
}