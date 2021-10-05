pkgname="gnuplot-gtk"
pkgver="5.4.2"
pkgrel="1"
pkgdesc="Plotting package which outputs to GTK4"
arch=("x86_64")
url="http://www.gnuplot.info"
depends=("readline" "cairo" "gtk4")
source=("gnuplot_gtk")
sha512sums=("skip")

package()
{
    mkdir -p "${pkgdir}/usr/bin"
    cp "${srcdir}/gnuplot_gtk" "${pkgdir}/usr/bin/gnuplot_gtk"
    chmod +x "${pkgdir}/usr/bin/gnuplot_gtk"
}
