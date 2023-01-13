package exercise;

public class J02_StoreList {
	public static void main(String[] args) {
		String macBrand="MacBookAir";
		double macSize=13.3;
		double macPrice=6999.88;
		int macCount=5;
		
		String thinkpadBrand="ThinkpadT450";
		double thinkpadSize=14.0;
		double thinkpadPrice=5888;
		int thinkpadount=10;
		
		String ASUSBrand="ASUS-FL5800";
		double ASUSSize=15.6;
		double ASUSPrice=64998.99;
		int ASUCount=16;
		
		System.out.println("--------------商品库存清单--------------");
		System.out.println("品牌型号         尺寸    价格     库存数");
		System.out.println(macBrand+"     "+macSize+"  "+macPrice+"   "+macCount);
		System.out.println(thinkpadBrand+"   "+thinkpadSize+"  "+thinkpadPrice+"    "+thinkpadount);
		System.out.println(ASUSBrand+"    "+ASUSSize+"  "+ASUSPrice+"  "+ASUCount);
	}
}
