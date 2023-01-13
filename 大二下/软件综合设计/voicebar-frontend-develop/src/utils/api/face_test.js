import apiAxios from "./axios"

export function uploadFaceTestImage(image_blob) { //上传人脸测试图像,返回评测结果
    const formdata = new FormData()
    formdata.append("image",image_blob,"ai_test.png")
    return apiAxios({
        url: `face_test/`,
        method: 'post',
        data: formdata,
        header: {
            'Content-Type' : 'multipart/form-data',
        },
    })
}

export function publishTestResult(result_id,title) { //分享人脸测试结果
    return apiAxios({
        url: `face_test/posts/`,
        method: 'post',
        data: {
            result_id:result_id,
            title:title,
        }
    })
}