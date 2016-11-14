import { Component, OnInit, Input } from '@angular/core';
import { CritiqueService } from '../../critique.service';
import { Observable } from 'rxjs/Rx';

@Component({
  selector: 'cle-critique-list',
  templateUrl: './critique-list.component.html',
  styleUrls: ['./critique-list.component.css']
})
export class CritiqueListComponent implements OnInit {
  @Input() submission;
  critiques: Observable<Any[]>;
  
  constructor(
    private critiqueService: CritiqueService
  ) { }

  ngOnInit() {
    this.critiqueService.getSubmissionCritiques(this.submission.nid)
      .subscribe(data => {
        this.critiques = data
        console.log(data);
      });
  }
}