*********************************************************************************        

    *** CVE-2020-25637 ***
                                        
*********************************************************************************
                                                   
    *** Description ***
                                                             
Un problème de double mémoire libre s'est produit dans l'API libvirt, dans les versions antérieures à la version 6.8.0, chargée de demander des informations sur les interfaces réseau d'un domaine QEMU en cours d'exécution. Cette faille affecte le pilote de contrôle d'accès polkit. Plus précisément, les clients se connectant au socket en lecture-écriture avec des autorisations ACL limitées pourraient utiliser cette faille pour planter le démon libvirt, entraînant un déni de service, ou potentiellement augmenter leurs privilèges sur le système. La plus grande menace de cette vulnérabilité concerne la confidentialité et l'intégrité des données ainsi que la disponibilité du système.

La menace la plus importante de cette vulnérabilité concerne :

* La confidentialité 
* L'intégrité des données
* La disponibilité du système.

Les scores de la faille :

* une faille juger modéré par RedHat avec une moyenne de 6.4

  * Vecteur            = Local
  * Complexité         = Faible
  * Authentification   = Aucune

* une faille juger modéré par NVD avec une moyenne de 6.7

  * Vecteur           = Local
  * Complexité        = Élevée 
  * Authentification  = Aucune
                                                   
        *** Diffèrent outils et prérequis importants a mettre en place pour exploiter cette faille ***
 
 1) Installation qemu-kvm et libvirt :

Avant tout il est nécessaire de vitrifier la compatibilité de notre système d'exploitation il suffit de passer cette commande:

     grep -E -c "vmx|svm" /proc/cpuinfo

Si la commande répond ok vous pouvez procéder a l'installation :

    sudo apt-get -y install qemu-kvm libvirt-bin virt-top outils-libguestfs virtinst bridge-utils
    
2) Installation vagrant :

Pour installer vagrant il suffit de passer cette commande :

    sudo apt -y install vagrant
    
Une fois que vous avez installé Vagrant et KVM, vous devriez être prêt à installer un plugin libvirt pour pouvoir commencer à gérer les machines virtuelles KVM à l'aide de Vagrant.

    vagrant plugin install vagrant-libvirt
    
vous pouvez confirmer que le plugin a été installé

    vagrant plugin list
    
3) Boite vagrant (box vagrant) :

Il est possible d’utiliser un modèle prêt directement par vagrant dans notre cas on utilisera une image ubuntu 20.04.

Pour ajouter notre image à la boite vagrant il suffit de passer cette commande :

    vagrant box add generic / ubuntu1804 --provider = libvirt
    
Pour Consulter la liste des boîtes présente localement :

    vagrant box list
 







 




 


 
 
