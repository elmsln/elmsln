import { Component, OnInit, Input } from '@angular/core';
import { Observable } from 'rxjs/Rx';
import { Critique } from '../../critique';
import { CritiqueService } from '../../critique.service';

@Component({
  selector: 'cle-critique-list',
  templateUrl: './critique-list.component.html',
  styleUrls: ['./critique-list.component.css']
})
export class CritiqueListComponent implements OnInit {
  @Input() submission;
  critiques: Observable<any[]>;
  
  constructor(
    private critiqueService: CritiqueService
  ) { }

  ngOnInit() {
    this.getCritiques();
  }

  getCritiques() {
    this.critiqueService.getSubmissionCritiques(this.submission.nid)
      .subscribe(data => {
        this.critiques = data
      });
  }
  

  deleteCritique(critique: Critique) {
    this.critiqueService.deleteCritique(critique)
      .subscribe(data => {
        console.log(data);
        this.getCritiques();
      })
  }
}