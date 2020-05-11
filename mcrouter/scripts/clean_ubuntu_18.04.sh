#!/usr/bin/env bash
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

set -ex

apt-get install -y libdouble-conversion1 libgflags2.2 \
    libboost-program-options1.65.1 libboost-filesystem1.65.1 \
    libboost-system1.65.1 libboost-regex1.65.1 libboost-thread1.65.1 \
    libboost-context1.65.1 libgoogle-glog0v5 libevent-2.1-6 libjemalloc1 \
    libicu-le-hb0 libharfbuzz0b libzstd1

apt-get purge -y gcc g++ ragel autoconf \
    git libtool python-dev libssl-dev libevent-dev \
    binutils-dev make libdouble-conversion-dev libgflags-dev \
    libgoogle-glog-dev libjemalloc-dev libicu-le-hb-dev

apt-get purge -y 'libboost.*-dev'
apt-get autoremove --purge -y
apt-get autoclean -y
apt-get clean -y

# OPTIONAL: Installs basic network tools to aid in debugging
apt-get --no-install-recommends -y install telnet traceroute ngrep net-tools \
    iftop mtr-tiny netcat iputils-ping

# IMPORTANT: Needed as folly is compiled against a specific version
# of zstd, which isn't available from Ubuntu upstream.
# See https://github.com/facebook/mcrouter/blob/
#     b7bd7d998f7a7a39ed827884dedb97d7966a5563/mcrouter/scripts/
#     recipes/folly.sh#L40-L41
# Without this, mcrouter fails to start with the following error:
#  mcrouter: error while loading shared libraries: libzstd.so.1.3.7: cannot
#  open shared object file: No such file or directory
cp -v /usr/local/mcrouter/install/lib/*.so.* /usr/lib/x86_64-linux-gnu/

if [[ "x$1" != "x" ]]; then
    PKG_DIR=$1/pkgs
    INSTALL_DIR=$1/install
    strip "$INSTALL_DIR"/bin/mcrouter
    rm -rf "$PKG_DIR"
    rm -rf "$INSTALL_DIR"/lib/*.a
    rm -rf "$INSTALL_DIR"/include
fi