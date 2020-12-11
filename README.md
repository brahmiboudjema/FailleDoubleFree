                                         *** CVE-2020-25637 ***
                                                   
                                         *** Description ***
                                                             
Un problème de double mémoire libre s'est produit dans l'API libvirt, dans les versions antérieures à la version 6.8.0, chargée de demander des informations sur les interfaces réseau d'un domaine QEMU en cours d'exécution. Cette faille affecte le pilote de contrôle d'accès polkit. Plus précisément, les clients se connectant au socket en lecture-écriture avec des autorisations ACL limitées pourraient utiliser cette faille pour planter le démon libvirt, entraînant un déni de service, ou potentiellement augmenter leurs privilèges sur le système. La plus grande menace de cette vulnérabilité concerne la confidentialité et l'intégrité des données ainsi que la disponibilité du système.
