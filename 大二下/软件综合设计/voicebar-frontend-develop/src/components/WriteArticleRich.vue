<template>
    <editor
    output-format="text"
    v-model="content"
    :init="init"/>
</template>

<script>
//tinyMCE
 /* Import TinyMCE */
 import tinymce from 'tinymce';

 /* Default icons are required for TinyMCE 5.3 or above */
 import 'tinymce/icons/default';

 /* A theme is also required */
 import 'tinymce/themes/silver';

 /* Import the skin */
 import 'tinymce/skins/ui/oxide/skin.css';

/* Import plugins */
 import 'tinymce/plugins/wordcount';

import Editor from '@tinymce/tinymce-vue'

const init = {
    skin: false,
    plugins: 'wordcount',
    language: 'zh-Hans',
    language_url: `/static/zh-Hans.js`,
    branding: false,
    elementpath: false,
    menubar: false,
    block_unsupported_drop: true,
    images_file_types: '',
    file_picker_types: '',
    height: 400,
    resize: false,
    toolbar: 'undo redo | selectall copy cut remove |',
    forced_root_block: false,
    }

export default {
    name: 'WriteArticleRich',
    emits: ['change'],
    data() {
        return {
            content: "",
        }
    },
    watch: {
        content() {
            this.$emit('change',this.content)
        }
    },
    components: {
        'editor':Editor
    },
    computed: {
        init() {
            return init
        }
    },
    mounted() {
        tinymce.init({
            elementpath: false,
            block_unsupported_drop: true,
            forced_root_block: false,
            menubar: false,
            resize: false,
            height: 410,
        })
    },
}

</script>

<style lang="scss">

</style>