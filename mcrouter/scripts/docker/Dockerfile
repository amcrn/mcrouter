FROM            ubuntu:18.04

MAINTAINER      mcrouter <mcrouter@fb.com>

ENV             MCROUTER_DIR            /usr/local/mcrouter
ENV             MCROUTER_REPO           https://github.com/amcrn/mcrouter.git
ENV             DEBIAN_FRONTEND         noninteractive
ARG             MAKE_JOBS=1
ARG             MCROUTER_BRANCH=master

RUN             apt-get update && apt-get -y install git && \
                mkdir -p $MCROUTER_DIR/repo && \
                cd $MCROUTER_DIR/repo && git clone -b $MCROUTER_BRANCH $MCROUTER_REPO && \
                cd $MCROUTER_DIR/repo/mcrouter/mcrouter/scripts && \
                sed -i -e 's/sudo //g' install_ubuntu_18.04.sh && \
                ./install_ubuntu_18.04.sh $MCROUTER_DIR -j$MAKE_JOBS && \
                ./clean_ubuntu_18.04.sh $MCROUTER_DIR && rm -rf $MCROUTER_DIR/repo && \
                ln -s $MCROUTER_DIR/install/bin/mcrouter /usr/local/bin/mcrouter && \
                rm -rf /var/lib/apt/lists/*

ENV             DEBIAN_FRONTEND newt