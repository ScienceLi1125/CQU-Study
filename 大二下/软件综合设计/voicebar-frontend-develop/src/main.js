import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

import { Cell, CellGroup, Button, Skeleton, Popup, Picker, Field, Form, NavBar, Tabbar, TabbarItem, Sticky, Icon, Uploader, Col, Row, Divider} from 'vant';
import { Toast } from 'vant';
import 'vant/es/toast/style';
import { Dialog } from 'vant';
import 'vant/es/dialog/style';
import { Image as VanImage } from 'vant';
import VueCropper from 'vue-cropper'; 
import 'vue-cropper/dist/index.css'
import { List } from 'vant';
import { ActionBar, ActionBarIcon, ActionBarButton } from 'vant';
import { Tag, PullRefresh, TreeSelect, Lazyload} from 'vant';

const app = createApp(App)
app.use(store).use(router)
app.use(Cell).use(CellGroup).use(Button).use(Skeleton).use(Popup).use(Picker).use(Field).use(Form).use(NavBar).use(Tabbar).use(TabbarItem).use(Sticky).use(Icon).use(VanImage).use(Uploader)
app.use(Divider).use(Col).use(Row).use(Tag)
app.use(Toast)
app.use(Dialog)
app.use(VueCropper)
app.use(List).use(ActionBar).use(ActionBarIcon).use(ActionBarButton).use(PullRefresh).use(TreeSelect)
app.use(Lazyload)
app.mount('#app')