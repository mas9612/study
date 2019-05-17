# Kubernetes Label/Selector

## Label
* key/value pair
* attached to various objects like Pod
* can be used to organize and to select subsets of objects

e.g.) Print Pods with labels
```sh
$ kubectl get pods --namespace kube-system --show-labels
NAME                               READY   STATUS    RESTARTS   AGE     LABELS
coredns-fb8b8dccf-hhm27            1/1     Running   0          3m      k8s-app=kube-dns,pod-template-hash=fb8b8dccf
coredns-fb8b8dccf-nrn5q            1/1     Running   0          3m      k8s-app=kube-dns,pod-template-hash=fb8b8dccf
etcd-minikube                      1/1     Running   0          117s    component=etcd,tier=control-plane
kube-addon-manager-minikube        1/1     Running   0          109s    component=kube-addon-manager,kubernetes.io/minikube-addons=addon-manager,version=v9.0
kube-apiserver-minikube            1/1     Running   0          2m12s   component=kube-apiserver,tier=control-plane
kube-controller-manager-minikube   1/1     Running   0          2m7s    component=kube-controller-manager,tier=control-plane
kube-proxy-vb8ml                   1/1     Running   0          3m      controller-revision-hash=6488cfdd59,k8s-app=kube-proxy,pod-template-generation=1
kube-scheduler-minikube            1/1     Running   0          2m7s    component=kube-scheduler,tier=control-plane
storage-provisioner                1/1     Running   0          2m58s   addonmanager.kubernetes.io/mode=Reconcile,integration-test=storage-provisioner
```

## Label selector
* client/user can identify a set of objects
* there are two types:
    - Equality-based requirement
    - Set-based requirement

### Equality-based requirement
```sh
# print only Pods which have label `k8s-app=kube-dns`
# k8s-app = kube-dns
$ kubectl get pods --namespace kube-system --show-labels --selector 'k8s-app = kube-dns'
NAME                      READY   STATUS    RESTARTS   AGE     LABELS
coredns-fb8b8dccf-hhm27   1/1     Running   0          4m31s   k8s-app=kube-dns,pod-template-hash=fb8b8dccf
coredns-fb8b8dccf-nrn5q   1/1     Running   0          4m31s   k8s-app=kube-dns,pod-template-hash=fb8b8dccf

# print only Pods which don't have label `k8s-app!=kube-dns`
# k8s-app != kube-dns
$ kubectl get pods --namespace kube-system --show-labels --selector 'k8s-app != kube-dns'
NAME                               READY   STATUS    RESTARTS   AGE     LABELS
etcd-minikube                      1/1     Running   0          4m20s   component=etcd,tier=control-plane
kube-addon-manager-minikube        1/1     Running   0          4m12s   component=kube-addon-manager,kubernetes.io/minikube-addons=addon-manager,version=v9.0
kube-apiserver-minikube            1/1     Running   0          4m35s   component=kube-apiserver,tier=control-plane
kube-controller-manager-minikube   1/1     Running   0          4m30s   component=kube-controller-manager,tier=control-plane
kube-proxy-vb8ml                   1/1     Running   0          5m23s   controller-revision-hash=6488cfdd59,k8s-app=kube-proxy,pod-template-generation=1
kube-scheduler-minikube            1/1     Running   0          4m30s   component=kube-scheduler,tier=control-plane
storage-provisioner                1/1     Running   0          5m21s   addonmanager.kubernetes.io/mode=Reconcile,integration-test=storage-provisioner
```

### Set-based requirement
```sh
# print only Pods which component label is etcd or kube-apiserver
# component in (etcd, kube-apiserver)
$ kubectl get pods --namespace kube-system --show-labels --selector 'component in (etcd, kube-apiserver)'
NAME                      READY   STATUS    RESTARTS   AGE     LABELS
etcd-minikube             1/1     Running   0          7m23s   component=etcd,tier=control-plane
kube-apiserver-minikube   1/1     Running   0          7m38s   component=kube-apiserver,tier=control-plane

# print only Pods which component label is not etcd or kube-apiserver
# component notin (etcd, kube-apiserver)
$ kubectl get pods --namespace kube-system --show-labels --selector 'component notin (etcd, kube-apiserver)'
NAME                               READY   STATUS    RESTARTS   AGE     LABELS
coredns-fb8b8dccf-hhm27            1/1     Running   0          9m      k8s-app=kube-dns,pod-template-hash=fb8b8dccf
coredns-fb8b8dccf-nrn5q            1/1     Running   0          9m      k8s-app=kube-dns,pod-template-hash=fb8b8dccf
kube-addon-manager-minikube        1/1     Running   0          7m49s   component=kube-addon-manager,kubernetes.io/minikube-addons=addon-manager,version=v9.0
kube-controller-manager-minikube   1/1     Running   0          8m7s    component=kube-controller-manager,tier=control-plane
kube-proxy-vb8ml                   1/1     Running   0          9m      controller-revision-hash=6488cfdd59,k8s-app=kube-proxy,pod-template-generation=1
kube-scheduler-minikube            1/1     Running   0          8m7s    component=kube-scheduler,tier=control-plane
storage-provisioner                1/1     Running   0          8m58s   addonmanager.kubernetes.io/mode=Reconcile,integration-test=storage-provisioner

# print only Pods which have label 'tier'
# tier
$ kubectl get pods --namespace kube-system --show-labels --selector 'tier'
NAME                               READY   STATUS    RESTARTS   AGE     LABELS
etcd-minikube                      1/1     Running   0          8m28s   component=etcd,tier=control-plane
kube-apiserver-minikube            1/1     Running   0          8m43s   component=kube-apiserver,tier=control-plane
kube-controller-manager-minikube   1/1     Running   0          8m38s   component=kube-controller-manager,tier=control-plane
kube-scheduler-minikube            1/1     Running   0          8m38s   component=kube-scheduler,tier=control-plane

# print only Pods which have label 'tier'
# !tier
$ kubectl get pods --namespace kube-system --show-labels --selector '!tier'
NAME                          READY   STATUS    RESTARTS   AGE     LABELS
coredns-fb8b8dccf-hhm27       1/1     Running   0          9m40s   k8s-app=kube-dns,pod-template-hash=fb8b8dccf
coredns-fb8b8dccf-nrn5q       1/1     Running   0          9m40s   k8s-app=kube-dns,pod-template-hash=fb8b8dccf
kube-addon-manager-minikube   1/1     Running   0          8m29s   component=kube-addon-manager,kubernetes.io/minikube-addons=addon-manager,version=v9.0
kube-proxy-vb8ml              1/1     Running   0          9m40s   controller-revision-hash=6488cfdd59,k8s-app=kube-proxy,pod-template-generation=1
storage-provisioner           1/1     Running   0          9m38s   addonmanager.kubernetes.io/mode=Reconcile,integration-test=storage-provisioner
```
